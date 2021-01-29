#include "../../inc/uchat_client.h"

void mx_write_language_data_from_bd(void) {
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "GetLanguage\n%d", t_user.id);
    send(sockfd, sendBuff, 256, 0);

    recv(sockfd, &language, sizeof(int), 0);
}
