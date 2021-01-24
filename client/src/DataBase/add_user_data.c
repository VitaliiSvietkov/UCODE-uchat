#include "../../inc/uchat_client.h"

void mx_add_user_data(const char *pseudo, const char *password, const char *name, char *sname) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT MAX(ID) FROM USERS;");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    int id = (int)sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    id++;
    char *description = " ";
    sprintf(sql, 
            "INSERT INTO USERS (ID, NAME, SURENAME, PSEUDONIM, \
            DESCRIPTION, PASSWORD, LANGUAGE, THEME) VALUES('%d',\
            '%s','%s','%s','%s','%s','%d','%d');", 
            id, name, sname, pseudo, description, password, 0, 0);   
    st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
    sqlite3_close(db);
    mx_write_photo_to_bd("client/img/ukraine.png", id);
}
