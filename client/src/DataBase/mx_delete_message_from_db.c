#include "../../inc/uchat_client.h"

void mx_delete_message_from_db(t_message *data) {
    sqlite3 *db = mx_opening_db();
    int st = 0;
    char *err_msg = 0;
    char sql[300];
    bzero(sql, 300);
    sprintf(sql, "DELETE FROM Messages WHERE id=%u AND\
            ((addresser=%u OR addresser=%u) AND (destination=%u OR destination=%u));", 
            data->id, curr_destination, t_user.id, curr_destination, t_user.id);
    st = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    mx_dberror(db, st, err_msg);

    sqlite3_stmt *res;
    bzero(sql, 300);
    sprintf(sql, "SELECT id FROM Messages WHERE id > %u AND\
            ((addresser=%u OR addresser=%u) AND (destination=%u OR destination=%u));", 
            data->id, curr_destination, t_user.id, curr_destination, t_user.id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    while (sqlite3_step(res) != SQLITE_DONE) {
        unsigned int value = (unsigned int)sqlite3_column_int64(res, 0);
        sprintf(sql, "UPDATE Messages SET id=%u WHERE id=%u AND\
            ((addresser=%u OR addresser=%u) AND (destination=%u OR destination=%u));", 
            value - 1, value, curr_destination, t_user.id, curr_destination, t_user.id);
        st = sqlite3_exec(db, sql, NULL, 0, &err_msg);
        mx_dberror(db, st, err_msg);
    }
    sqlite3_finalize(res);

    sqlite3_close(db);
}
