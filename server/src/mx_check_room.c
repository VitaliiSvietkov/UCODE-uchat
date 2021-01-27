#include "../inc/server.h"

void mx_check_room(char **data, int sockfd) {
    int uid = mx_atoi(data[1]);
    int dst = mx_atoi(data[2]);
    int return_val = 0;

    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res = NULL;
    char sql[250];
    bzero(sql, 250);
    sprintf(sql, "SELECT id FROM Messages\
            WHERE (addresser=%d OR destination=%d) AND (addresser=%d OR destination=%d);", 
            dst, uid, dst, uid);

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (sqlite3_step(res) != SQLITE_DONE)
        send(sockfd, &return_val, sizeof(int), 0);
    else {
        return_val++;
        send(sockfd, &return_val, sizeof(int), 0);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}
