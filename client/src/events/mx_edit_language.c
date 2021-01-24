#include "../../inc/uchat_client.h"

void mx_edit_language(int language) {
    sqlite3 *db = mx_opening_db();
    char sql[500];
    bzero(sql, 500);
    char *errmsg;
    sprintf(sql, "UPDATE USERS SET LANGUAGE=%d WHERE ID=%d;", language, t_user.id);   
    int st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
    sqlite3_close(db);
}
