#include "../inc/server.h"

/*
    data - recv data from client
    data[0] - Operation
    data[1] - id
    data[2] - addresser
    data[3] - destination
    data[4] - time
    data[4] - NULL
*/

void mx_insert_message(char **data, int sockfd) {
    char text[1024];
    recv(sockfd, text, 1024, 0);

    sqlite3 *db = mx_opening_db();
    char *err_msg;
    char sql[1024];
    bzero(sql, 1024);
    sprintf(sql, "INSERT INTO Messages (id, addresser, destination, Text, time)\
            VALUES('%u','%u','%u','%s','%d');", 
            mx_atoi(data[1]), mx_atoi(data[2]), mx_atoi(data[3]), text, mx_atoi(data[4]));
    int st = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    mx_dberror(db, st, err_msg);
    sqlite3_close(db);
}
