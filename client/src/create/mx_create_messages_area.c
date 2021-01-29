#include "../../inc/uchat_client.h"

void mx_create_messages_area(void) {
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_HEIGHT - 50, 100, 100, CUR_HEIGHT - 50);
    t_chat_room_vars.right_container = gtk_scrolled_window_new(NULL, vadjustment);
    gtk_widget_set_size_request(GTK_WIDGET(t_chat_room_vars.right_container), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_fixed_put(GTK_FIXED(chat_area), t_chat_room_vars.right_container, L_FIELD_WIDTH, 0);
    t_chat_room_vars.messages_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(t_chat_room_vars.right_container), "chat_background");
    gtk_widget_set_size_request(GTK_WIDGET(t_chat_room_vars.messages_box), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_container_add(GTK_CONTAINER(t_chat_room_vars.right_container), t_chat_room_vars.messages_box);

    char sendBuff[1024];
    sprintf(sendBuff, "LoadRoom\n%u\n%u", t_user.id, curr_destination);
    send(sockfd, sendBuff, 1024, 0);

    recv(sockfd, &max_msg_id, sizeof(int), 0);

    if (max_msg_id > 0) {
        char recvBuff[1024];
        bzero(recvBuff, 1024);
        for (int i = 0; i < max_msg_id; i++) {
            recv(sockfd, recvBuff, 1024, 0);

            int cur_m_id = 0;
            recv(sockfd, &cur_m_id, sizeof(int), 0);

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
                cur_m_id);

            mx_del_strarr(&recvData);
            bzero(recvBuff, 1024);
        }

        t_message *msg = curr_room_msg_head;
        while (msg != NULL) {
            mx_add_message(t_chat_room_vars.messages_box, msg);
            //max_msg_id = msg->id;
            msg = msg->next;
        }
    }

    gtk_widget_show_all(GTK_WIDGET(t_chat_room_vars.right_container));
}
