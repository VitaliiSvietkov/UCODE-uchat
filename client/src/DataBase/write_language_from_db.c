#include "../../inc/uchat_client.h"

void mx_write_language_data_from_bd(void) {
<<<<<<< HEAD
    sqlite3 *db = mx_opening_db("test");
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT LANGUAGE FROM LANGUAGE;");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    language = (int)sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    //sqlite3_close(db);
=======
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "GetLanguage\n%d", t_user.id);
    send(sockfd, sendBuff, 256, 0);

    recv(sockfd, &language, sizeof(int), 0);
>>>>>>> main
}
