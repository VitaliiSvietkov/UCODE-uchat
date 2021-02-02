#include "../../inc/uchat_client.h"

// Add button
//=================================================================================
void mx_attach(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    mx_destroy_popups();
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        dialog = gtk_file_chooser_dialog_new ("Select an Image",
                                            GTK_WINDOW(window),
                                            action,
                                            "_Cancel",
                                            GTK_RESPONSE_CANCEL,
                                            "_Select",
                                            GTK_RESPONSE_ACCEPT,
                                            NULL);

        GtkFileFilter *filter = gtk_file_filter_new();
        char *pattern_arr[13] = {"*.tif", "*.tiff", "*.bmp", "*.jpg", "*.jpeg", "*.gif",
            "*.png", "*.eps", "*.raw", "*.cr2", "*.nef", "*.orf", "*.sr2"};
        for (int i = 0; i < 13; ++i)
            gtk_file_filter_add_pattern(filter, pattern_arr[i]);
        gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        char *filename = NULL;
        if (res == GTK_RESPONSE_ACCEPT)
        {
            GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
            filename = gtk_file_chooser_get_filename (chooser);
        }
        gtk_widget_destroy (dialog);

        if (filename != NULL) {
            struct stat buf;
            stat(filename, &buf);
            if (buf.st_size < 7971520) // < 8mb
                mx_create_attach_form(entry, filename);
            else {
                pthread_t thread_id;
                char *err_msg = "The file is too big!";
                pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                //mx_run_error_pop_up("The file is too big!");
            }
        }
    }
}

void mx_attach_send_message_on_enter(GtkWidget *widget, void **arr) {
    GdkPixbuf *pixbuf = arr[1];
    time_t curtime;
    time(&curtime);

    char *text = NULL;
    if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        text = strdup(gtk_entry_get_text(GTK_ENTRY(widget)));
    
    t_message *msg = NULL;
    sqlite3 *db = mx_opening_local_db();
    char *err_msg = 0;
    char sql[500];
    if (gdk_pixbuf_get_width(GDK_PIXBUF(pixbuf)) > 350) {
        msg = mx_push_back_message(&curr_room_msg_head,
            NULL, 
            t_user.id, 
            pixbuf,
            curtime,
            max_msg_id);
        mx_add_message(t_chat_room_vars.messages_box, msg);
        sprintf(sql,
                "INSERT INTO Messages (id, addresser, destination, time)\
                VALUES('%u','%u','%u','%ld');",
                msg->id, t_user.id, curr_destination, msg->seconds);
        sqlite3_exec(db, sql, 0, 0, &err_msg);
        mx_write_image_message((char *)arr[0], msg->id);

        if (text != NULL) {
            msg = mx_push_back_message(&curr_room_msg_head,
                text, 
                t_user.id, 
                NULL,
                curtime,
                max_msg_id);
            mx_add_message(t_chat_room_vars.messages_box, msg);

            sprintf(sql,
                    "INSERT INTO Messages (id, addresser, destination, Text, time)\
                    VALUES('%u','%u','%u','%s','%ld');",
                    msg->id, t_user.id, curr_destination, msg->text, msg->seconds);
            sqlite3_exec(db, sql, 0, 0, &err_msg);
        }
    }
    else {
        char sendBuff[2056];
        bzero(sendBuff, 2056);
        const gchar *m_text = gtk_entry_get_text(GTK_ENTRY(widget));
        if (mx_strlen(m_text) == 0)
            m_text = "(null)";
        sprintf(sendBuff, "InsertMessage\n%u\n%u\n%lu\n%s",
                t_user.id, curr_destination, curtime, m_text);
        
        if(send(sockfd, sendBuff, 2056, 0) == -1){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return;
        }

        int m_id = 0;
        if(recv(sockfd, &m_id, sizeof(int), 0) == 0){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return;
        }
        max_msg_id = m_id;

        msg = mx_push_back_message(&curr_room_msg_head,
            text, 
            t_user.id, 
            pixbuf,
            curtime,
            max_msg_id);
        mx_add_message(t_chat_room_vars.messages_box, msg);

        printf("I AM GOINT TO SEND!\n");

        mx_write_image_message((char *)arr[0], msg->id);
    }
    sqlite3_close(db);

    gtk_widget_destroy(GTK_WIDGET(blackout));
    blackout = NULL;
    g_free(arr);

    gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(chat_area));
}
//=================================================================================

// Message entry field
//=================================================================================
void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event) {
    mx_destroy_popups();
    int len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    GList *children = gtk_container_get_children(GTK_CONTAINER(t_chat_room_vars.message_enter_area));
    if (len > 0) {
        gtk_widget_hide(GTK_WIDGET(g_list_nth_data(children, 2)));
        gtk_widget_show(GTK_WIDGET(g_list_nth_data(children, 3)));
    }
    else {
        gtk_widget_hide(GTK_WIDGET(g_list_nth_data(children, 3)));
        gtk_widget_show(GTK_WIDGET(g_list_nth_data(children, 2)));
    }
    g_list_free(children);
}

void mx_send_message_on_enter(GtkWidget *widget) {
    if (sockfd == -1){
        mx_connect_to_server();
        //return 1;
    }

    if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0) {
        time_t curtime;
        time(&curtime);

        char sendBuff[2056];
        bzero(sendBuff, 2056);
        sprintf(sendBuff, "InsertMessage\n%u\n%u\n%lu\n%s",
                t_user.id, curr_destination, curtime, gtk_entry_get_text(GTK_ENTRY(widget)));
        
        if(send(sockfd, sendBuff, 2056, 0) == -1){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return;
        }

        int m_id = 0;
        if(recv(sockfd, &m_id, sizeof(int), 0) == 0){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return;
        }
        max_msg_id = m_id;

        t_message *msg = mx_push_back_message(&curr_room_msg_head,
            strdup(gtk_entry_get_text(GTK_ENTRY(widget))), 
            t_user.id, 
            NULL,
            curtime,
            m_id);
        mx_add_message(t_chat_room_vars.messages_box, msg);

        gtk_entry_set_text(GTK_ENTRY(widget), "");
    }
}
//=================================================================================

// Tick button
//=================================================================================
void mx_send_message(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    if (sockfd == -1){
        mx_connect_to_server();
        //return 1;
    }

    mx_destroy_popups();
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0) {
            if (edit_prev == NULL) {
                time_t curtime;
                time(&curtime);

                char sendBuff[2056];
                bzero(sendBuff, 2056);
                sprintf(sendBuff, "InsertMessage\n%u\n%u\n%lu\n%s",
                    t_user.id, curr_destination, curtime, gtk_entry_get_text(GTK_ENTRY(entry)));
                
                int error = 0;
                socklen_t len = sizeof(error);
                int retval = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
                if (retval != 0) {
                    fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
                    sockfd = -1;
                    return;
                }
                if (error != 0) {
                    fprintf(stderr, "socket error: %s\n", strerror(error));
                    sockfd = -1;
                    return;
                }
                
                if(send(sockfd, sendBuff, 2056, 0) == -1){
                    pthread_t thread_id;
                    char *err_msg = "Connection lost\nTry again later";
                    pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                    sockfd = -1;
                    return;
                }


                int m_id = 0;
                if(recv(sockfd, &m_id, sizeof(int), 0) == 0){
                    pthread_t thread_id;
                    char *err_msg = "Connection lost\nTry again later";
                    pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
                    sockfd = -1;
                    return;
                }
                max_msg_id = m_id;

                t_message *msg = mx_push_back_message(&curr_room_msg_head,
                    strdup(gtk_entry_get_text(GTK_ENTRY(widget))), 
                    t_user.id, 
                    NULL,
                    curtime,
                    m_id);
                mx_add_message(t_chat_room_vars.messages_box, msg);

                sqlite3 *db = mx_opening_local_db();
                int st;
                char *err_msg;
                char sql[500];
                bzero(sql, 500);
                sprintf(sql, "INSERT INTO Messages (id, addresser, destination, Text, time)\
                    VALUES('%u','%u','%u','%s','%ld');", 
                    msg->id, t_user.id, curr_destination, msg->text, msg->seconds);
                st = sqlite3_exec(db, sql, NULL, 0, &err_msg);
                mx_dberror(db, st, err_msg);
                sqlite3_close(db);

                gtk_entry_set_text(GTK_ENTRY(widget), "");
                t_chats_list *node = chats_list_head;
                while (node->uid != (int)curr_destination)
                    node = node->next;
                gtk_box_reorder_child(GTK_BOX(chats_list), node->room, 0);
            }
            else {
                char *text = mx_strdup(gtk_entry_get_text(GTK_ENTRY(widget)));

                GList *children = gtk_container_get_children(GTK_CONTAINER(selected_msg_widget));
                GList *box_children = gtk_container_get_children(GTK_CONTAINER(g_list_nth_data(children, 0)));
                guint size = g_list_length(box_children);
                gtk_label_set_text(GTK_LABEL(g_list_nth_data(box_children, size - 2)), text);
                g_list_free(children);
                g_list_free(box_children);

                free(selected_msg_struct->text);
                selected_msg_struct->text = text;
                
                gtk_widget_destroy(GTK_WIDGET(edit_prev));
                edit_prev = NULL;
                children = gtk_container_get_children(GTK_CONTAINER(t_chat_room_vars.message_enter_area));
                gtk_entry_set_text(GTK_ENTRY(g_list_nth_data(children, 1)), "");
                gtk_widget_set_can_focus(GTK_WIDGET(g_list_nth_data(children, 1)), TRUE);
                gtk_widget_grab_focus(GTK_WIDGET(g_list_nth_data(children, 1)));
                g_list_free(children);

                char sendBuff[256];
                bzero(sendBuff, 256);
                sprintf(sendBuff, "EditMessage\n%d\n%d\n%d\n%s", t_user.id, (int)curr_destination,
                    (int)selected_msg_struct->id, text);

                send(sockfd, sendBuff, 256, 0);
            }
        }
    }
}
//=================================================================================

// More button
//=================================================================================
void more_content_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
        if (!(flags & GTK_STATE_FLAG_CHECKED)) {

            flags = gtk_widget_get_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 1, 1)));
            if (flags & GTK_STATE_FLAG_CHECKED) {
                gtk_widget_unset_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 1, 1)), GTK_STATE_FLAG_CHECKED);
            }
            else {
                gtk_widget_unset_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 3, 1)), GTK_STATE_FLAG_CHECKED);
            }

            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, TRUE);

        }
    }
}

void mx_more_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
        if (!(flags & GTK_STATE_FLAG_CHECKED)) {
            mx_destroy_popups();
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);

            t_chat_room_vars.more_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(t_chat_room_vars.more_box), "more_box");
            GtkAllocation alloc;
            gtk_widget_get_allocation(GTK_WIDGET(widget), &alloc);
            gtk_fixed_put(GTK_FIXED(chat_area), t_chat_room_vars.more_box, alloc.x - 265, alloc.y - 515);

            GtkWidget *more_grid = gtk_grid_new();
            gtk_container_add(GTK_CONTAINER(t_chat_room_vars.more_box), more_grid);
            gtk_widget_set_valign(GTK_WIDGET(more_grid), GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(GTK_WIDGET(more_grid), 300, 480);
            gtk_widget_set_margin_top(GTK_WIDGET(more_grid), 10);
            gtk_widget_set_margin_bottom(GTK_WIDGET(more_grid), 10);

            GtkWidget *stickers_eventbox = gtk_event_box_new();
            gtk_widget_set_size_request(GTK_WIDGET(stickers_eventbox), 150, 45);
            gtk_widget_set_name(GTK_WIDGET(stickers_eventbox), "stickers_eventbox");
            gtk_widget_set_state_flags(GTK_WIDGET(stickers_eventbox), GTK_STATE_FLAG_CHECKED, TRUE);
            g_signal_connect(G_OBJECT(stickers_eventbox), "button_press_event",
                G_CALLBACK(more_content_click), more_grid);
            gtk_grid_attach(GTK_GRID(more_grid), stickers_eventbox, 1, 1, 2, 1);

            GtkWidget *gifs_eventbox = gtk_event_box_new();
            gtk_widget_set_size_request(GTK_WIDGET(gifs_eventbox), 150, 45);
            gtk_widget_set_name(GTK_WIDGET(gifs_eventbox), "gifs_eventbox");
            g_signal_connect(G_OBJECT(gifs_eventbox), "button_press_event",
                G_CALLBACK(more_content_click), more_grid);
            gtk_grid_attach(GTK_GRID(more_grid), gifs_eventbox, 3, 1, 1, 1);
            
            
            gtk_widget_show_all(GTK_WIDGET(t_chat_room_vars.more_box));
        }
        else {
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED);

            gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.more_box));
            t_chat_room_vars.more_box = NULL;
        }
    }
}
//=================================================================================
