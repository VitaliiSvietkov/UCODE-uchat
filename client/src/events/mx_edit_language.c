#include "../../inc/uchat_client.h"

void mx_edit_language(int language) {
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "UpdateLanguage\n%d\n%d", language, t_user.id);
    send(sockfd, sendBuff, 256, 0);
}
