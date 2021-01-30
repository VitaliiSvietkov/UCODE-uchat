#include "../../inc/uchat_client.h"

void mx_delete_message_from_db(t_message *data) {
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "DeleteMessage\n%d\n%d\n%d", t_user.id, curr_destination, (int)data->id);
    send(sockfd, sendBuff, 256, 0);
}
