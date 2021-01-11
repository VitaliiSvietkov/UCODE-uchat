#include "../../inc/uchat_client.h"

void mx_create_messages_area(void) {
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_HEIGHT - 50, 100, 100, CUR_HEIGHT - 50);
    right_container = gtk_scrolled_window_new(NULL, vadjustment);
    gtk_widget_set_size_request(GTK_WIDGET(right_container), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_fixed_put(GTK_FIXED(chat_area), right_container, L_FIELD_WIDTH, 0);
    messages_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(right_container), "chat_background");
    gtk_widget_set_size_request(GTK_WIDGET(messages_box), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_container_add(GTK_CONTAINER(right_container), messages_box);

    t_message *msg = NULL;
    sqlite3_stmt *res = NULL;
    char sql[35];
    bzero(sql, 35);
    char *err_msg;
    sprintf(sql, "SELECT uid, Text FROM Messages;");
    sqlite3_prepare_v2(messages_db, sql, -1, &res, 0);
    while (sqlite3_step(res) != SQLITE_DONE) {
        msg = mx_push_back_message(&curr_room_msg_head, 
            mx_strdup((char *)sqlite3_column_text(res, 1)), 
            (unsigned int)sqlite3_column_int64(res, 0),
            NULL);
        mx_add_message(messages_box, msg);
    }
    if (res != NULL)
        sqlite3_finalize(res);

    gtk_widget_show_all(GTK_WIDGET(right_container));
}
