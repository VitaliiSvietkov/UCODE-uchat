#include "../../inc/uchat_client.h"

<<<<<<< HEAD
void mx_add_user_data(const char *pseudo, const char *password, const char *name, const char *sname) {
    sqlite3 *db = mx_opening_db("test");
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

    /*sprintf(sql, "SELECT PSEUDONIM FROM USERS;");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    char *check_pseudo;
    int status = 0;
    while(sqlite3_column_text(res, 0) != NULL) {
        check_pseudo = mx_string_copy((char *)sqlite3_column_text(res, 0));
        if(mx_strcmp(pseudo, check_pseudo) == 0){
            mx_write_to_log("USER EXISTS", 2);
            status = 1;
            sqlite3_close(db);
        }
        sqlite3_step(res);
=======
void mx_add_user_data(const char *pseudo, const char *password, const char *name, char *sname) {
    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "AddUser\n%s\n%s\n%s\n%s", name, sname, pseudo, password);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
>>>>>>> main
    }
}
