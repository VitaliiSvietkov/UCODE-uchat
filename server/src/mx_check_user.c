#include "../inc/server.h"

sqlite3 *mx_opening_db(void) {
    sqlite3 *db;
    int status = sqlite3_open("server/data/test.db", &db);
    if (status != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
    }
    return db;
}

bool mx_check_user(char **data) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE PSEUDONIM='%s';", data[1]);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (sqlite3_step(res) != SQLITE_DONE) {
        char *check_password = mx_strdup((char *)sqlite3_column_text(res, 0));
        if (mx_strcmp(check_password, data[2]) == 0) {
            free(check_password);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return true;
        }
        else {
            free(check_password);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return false; 
        }
    }
    else {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return false; 
    }
}
