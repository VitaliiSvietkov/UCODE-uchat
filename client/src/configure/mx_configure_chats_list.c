#include "../../inc/uchat_client.h"

void mx_configure_chats_list(void) {
    chats_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), chats_list, 0, 105);

    sqlite3 *db = mx_opening_db();
    t_message *msg = NULL;
    sqlite3_stmt *res = NULL;
    char sql[250];
    bzero(sql, 250);
    char *err_msg;
    sprintf(sql, "SELECT addresser, destination FROM Messages\
            WHERE addresser=%u OR destination=%u;",
            t_user.id, t_user.id);

    unsigned int *uid_arr = NULL;
    int uid_arr_len = 0;
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    while (sqlite3_step(res) != SQLITE_DONE) {
        unsigned int addresser = (unsigned int)sqlite3_column_int64(res, 0);
        unsigned int destination = (unsigned int)sqlite3_column_int64(res, 1);
        if (addresser != (unsigned int)t_user.id && !mx_uint_arr_check_value(uid_arr, addresser, uid_arr_len))
            uid_arr_len = mx_uint_array_insert(&uid_arr, addresser, uid_arr_len);
        if (destination != (unsigned int)t_user.id && !mx_uint_arr_check_value(uid_arr, destination, uid_arr_len))
            uid_arr_len = mx_uint_array_insert(&uid_arr, destination, uid_arr_len);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

    for (int i = 0; i < uid_arr_len; i++)
        gtk_box_pack_start(GTK_BOX(chats_list), mx_create_room(uid_arr[i], L_FIELD_WIDTH, room_click), FALSE, FALSE, 0);
    
    free(uid_arr);
    uid_arr = NULL;
}
