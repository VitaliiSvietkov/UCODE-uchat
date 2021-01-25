#include "../../inc/uchat_client.h"

void mx_edit_name(char* name, char* surname, char* pseudo, char *description, int id) {
    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "UpdateUserData\n%s\n%s\n%s\n%s\n%d", 
            name, surname, pseudo, description, id);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }
}
