#include "../../inc/uchat_client.h"

void mx_add_user_data(const char *pseudo, const char *password, const char *name, char *sname) {
    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "AddUser\n%s\n%s\n%s\n%s", name, sname, pseudo, password);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }
}
