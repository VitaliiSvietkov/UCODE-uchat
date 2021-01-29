#include "../inc/server.h"

/*
    data - recv data from client
    data[0] - Operation
    data[1] - addresser
    data[2] - destination
    data[3] - time
    data[4...n-1] - text
    data[n] - NULL
*/

void mx_insert_message(char **data, int sockfd) {
    char *text = NULL;
    for (int i = 4; data[i] != NULL; i++)
        text = mx_strjoin(text, data[i]);

    int addresser = mx_atoi(data[1]);
    int destination = mx_atoi(data[2]);

    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[2056];
    bzero(sql, 2056);
    char *errmsg;
    sprintf(sql, "SELECT MAX(ID) FROM Messages WHERE (addresser=%u OR addresser=%u) AND (destination=%u OR destination=%u);",
        addresser, destination, addresser, destination);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    int id = (int)sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    id++;

    char *err_msg;
    bzero(sql, 2056);
    sprintf(sql, "INSERT INTO Messages (id, addresser, destination, Text, time)\
            VALUES('%u','%u','%u','%s','%d');", 
            id, addresser, destination, text, mx_atoi(data[3]));
    int st = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    mx_dberror(db, st, err_msg);
    sqlite3_close(db);

    free(text);
}
