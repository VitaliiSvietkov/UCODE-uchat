#include "../../inc/uchat_client.h"

void mx_edit_language(int language) {
<<<<<<< HEAD
    sqlite3 *db = mx_opening_db("test");
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT LANGUAGE FROM LANGUAGE;");
    int edit_language;
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    edit_language = (int)sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sprintf(sql, "UPDATE LANGUAGE SET LANGUAGE = REPLACE(LANGUAGE, '%d' ,'%d');", edit_language, language);   
    st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
=======
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "UpdateLanguage\n%d\n%d", language, t_user.id);
    send(sockfd, sendBuff, 256, 0);
>>>>>>> main
}
