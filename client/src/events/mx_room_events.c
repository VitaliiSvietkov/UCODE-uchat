#include "../../inc/uchat_client.h"

void *check_messages(void *data) {
    if (sockfd == -1){
        mx_connect_to_server();
        //return 1;
    }

    while (true) {
        char sendBuff[256];
        bzero(sendBuff, 256);
        sprintf(sendBuff, "CheckMessages\n%d\n%d\n%d", (int)t_user.id, (int)curr_destination, (int)max_msg_id);
        
        int error = 0;
        socklen_t len = sizeof (error);
        int retval = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
        if (retval != 0) {
            fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
            sockfd = -1;
            return NULL;
        }
        if (error != 0) {
            fprintf(stderr, "socket error: %s\n", strerror(error));
            sockfd = -1;
            return NULL;
        }
        
        if(send(sockfd, sendBuff, 256, 0) == -1){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return NULL;
        }

        int latest = max_msg_id;
        if(recv(sockfd, &latest, sizeof(int), 0) == 0){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return NULL;
        }

        if (latest == max_msg_id) {
            //printf("UP TO DATE\n");
            usleep(500000);
            continue;
        }
        else if (latest < max_msg_id) {
            gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.right_container));
            if (curr_room_msg_head != NULL)
                mx_clear_message_list(&curr_room_msg_head);
            mx_create_messages_area();
        }
        else {
            bzero(sendBuff, 256);
            sprintf(sendBuff, "LoadMessages\n%d\n%d\n%d", (int)t_user.id, (int)curr_destination, (int)max_msg_id);
            if(send(sockfd, sendBuff, 256, 0) == -1){
                pthread_t thread_id;
                char *err_msg = "Connection lost\nTry again later";
                pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                sockfd = -1;
                return NULL;
            }

            latest = 0;
            if(recv(sockfd, &latest, sizeof(int), 0) ==0){
                pthread_t thread_id;
                char *err_msg = "Connection lost\nTry again later";
                pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                sockfd = -1;
                return NULL;
            }

            char recvBuff[1024];
            bzero(recvBuff, 1024);
            for (int i = max_msg_id; i < latest; i++) {
                if(recv(sockfd, recvBuff, 1024, 0) ==0){
                pthread_t thread_id;
                char *err_msg = "Connection lost\nTry again later";
                pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                sockfd = -1;
                return NULL;
            }

                int m_id = 0;
                if(recv(sockfd, &m_id, sizeof(int), 0) ==0){
                pthread_t thread_id;
                char *err_msg = "Connection lost\nTry again later";
                pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                sockfd = -1;
                return NULL;
            }

                char **recvData = mx_strsplit(recvBuff, '\n');
                int msg_id = mx_atoi(recvData[0]);
                int msg_addresser = mx_atoi(recvData[1]);
                int seconds = mx_atoi(recvData[3]);
                char *text = NULL;
                if (mx_strcmp("(null)", recvData[2]))
                    text = mx_strdup(recvData[2]);

                // Change NULL for mx_read_image_message((unsigned int)sqlite3_column_int64(res, 0), db)
                mx_push_back_message(&curr_room_msg_head, 
                    text, 
                    msg_addresser,
                    NULL,
                    seconds,
                    m_id);

                mx_del_strarr(&recvData);
                bzero(recvBuff, 1024);
            }

            t_message *msg = mx_message_search(&curr_room_msg_head, max_msg_id + 1);
            while (msg != NULL) {
                mx_add_message(t_chat_room_vars.messages_box, msg);
                max_msg_id = msg->id;
                msg = msg->next;
            }
        }
    }
}

void room_click(GtkWidget *widget, GdkEventButton *event, gpointer uid) {
    mx_destroy_popups();
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        curr_destination = (unsigned int)(uintptr_t)uid;

        if (max_msg_id > 0) {
            pthread_cancel(check_messages_id);
            max_msg_id = 0;
        }

        char *err_msg = 0;
        if (t_chat_room_vars.message_enter_area != NULL) {
            gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.message_enter_area));
            t_chat_room_vars.message_enter_area = NULL;
        }
        if (t_chat_room_vars.right_container != NULL) {
            gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.right_container));
            t_chat_room_vars.right_container = NULL;
        }
        if (curr_room_msg_head != NULL)
            mx_clear_message_list(&curr_room_msg_head);

        mx_create_messages_area();
        mx_create_message_enter_area();

        gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(chat_area));

        pthread_create(&check_messages_id, NULL, check_messages, NULL);
    }
}


// Close a room on the Esc button press
void room_close(GtkWidget *widget, GdkEventKey *event) {
    switch (event->keyval) {
        case GDK_KEY_Escape:
            if (blackout != NULL) {
                gtk_widget_destroy(GTK_WIDGET(blackout));
                if (NewFirstName != NULL) {
                    free(NewFirstName);
                    NewFirstName = NULL;
                    free(NewPseudonim);
                    NewPseudonim = NULL;
                    free(NewDescription);
                    NewDescription = NULL;
                    g_object_unref(G_OBJECT(NewAvatar));
                    NewAvatar = NULL;
                }
                if (NewSecondName != NULL) {
                    free(NewSecondName);
                    NewSecondName = NULL;
                }
                blackout = NULL;

                gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
                gtk_widget_grab_focus(GTK_WIDGET(chat_area));
                break;
            }
            mx_destroy_popups();
            if (t_chat_room_vars.message_enter_area != NULL) {
                gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.message_enter_area));
                t_chat_room_vars.message_enter_area = NULL;
                gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.right_container));
                t_chat_room_vars.right_container = NULL;
            }
            if (curr_room_msg_head != NULL)
                mx_clear_message_list(&curr_room_msg_head);
            pthread_cancel(check_messages_id);
            max_msg_id = 0;
            break;
        default:
            break;
    }
}
