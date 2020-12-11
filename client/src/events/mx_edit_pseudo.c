#include "../../inc/uchat_client.h"

void mx_edit_pseudo(char *pseudo) {
    sqlite3 *db = mx_opening_db();
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "REPLACE INTO USERS (PSEUDONIM) VALUES('%s');", pseudo);   
    printf("%s\n", pseudo); 
    st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
}
