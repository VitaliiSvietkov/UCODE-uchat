#include "../inc/uchat_client.h"

void mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* password) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    char *check_password = mx_string_copy((char *)sqlite3_column_text(res, 0));
    if (mx_strcmp(check_password, password) == 0) {
        sprintf(sql, "SELECT ID, NAME, SURENAME, PSEUDONIM, DESCRIPTION FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        sqlite3_step(res);
        int newId = (int)sqlite3_column_int(res, 0);
        t_user.id = newId;
        char *newName = mx_string_copy((char *)sqlite3_column_text(res, 1));
        t_user.FirstName = newName;
        char *newSName = mx_string_copy((char *)sqlite3_column_text(res, 2));
        t_user.SecondName = newSName;
        char *newPseudo = mx_string_copy((char *)sqlite3_column_text(res, 3));
        t_user.pseudonim = newPseudo;
        char *newDescr = mx_string_copy((char *)sqlite3_column_text(res, 4));
        t_user.description = newDescr;
        char *newPass = check_password;
        t_user.password = newPass;
    }
    else {
        mx_write_to_log("USER NOT EXIST", 2);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}