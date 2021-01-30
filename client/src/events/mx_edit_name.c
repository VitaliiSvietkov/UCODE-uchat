#include "../../inc/uchat_client.h"

void mx_edit_name(char* name, char* surname, char* pseudo, char *description, int id) {
<<<<<<< HEAD
    sqlite3 *db = mx_opening_db("test");
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    if (surname == NULL) {
        surname = " ";
=======
    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "UpdateUserData\n%s\n%s\n%s\n%s\n%d", 
            name, surname, pseudo, description, id);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
>>>>>>> main
    }
}
