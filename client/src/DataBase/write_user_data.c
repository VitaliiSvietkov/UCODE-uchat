#include "../../inc/uchat_client.h"

void mx_write_user_data_from_bd(void) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT ID, NAME, SURENAME, PSEUDONIM, DESCRIPTION, PASSWORD FROM USERS;");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    t_user.id = (int)sqlite3_column_int(res, 0);
    t_user.FirstName = mx_string_copy((char *)sqlite3_column_text(res, 1));
    t_user.SecondName = mx_string_copy((char *)sqlite3_column_text(res, 2));
    t_user.pseudonim  = mx_string_copy((char *)sqlite3_column_text(res, 3));
    t_user.description = mx_string_copy((char *)sqlite3_column_text(res, 4));
    t_user.password = mx_string_copy((char *)sqlite3_column_text(res, 5));
    sqlite3_finalize(res);
    sqlite3_close(db);
}
