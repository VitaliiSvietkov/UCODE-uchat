#include "../../inc/uchat_client.h"

void mx_configure_chats_list(void) {
    chats_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), chats_list, 0, 105);

    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "GetUsersArr\n%d", t_user.id);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }
    
    int rooms_uids_len = 0;
    recv(sockfd, &rooms_uids_len, sizeof(int), 0);

    unsigned int *rooms_uids = (unsigned int *)malloc(rooms_uids_len);
    for (int i = 0; i < rooms_uids_len; i++)
        recv(sockfd, &rooms_uids[i], sizeof(unsigned int), 0);
    
    for (int i = 0; i < rooms_uids_len; i++)
        gtk_box_pack_start(GTK_BOX(chats_list), 
            mx_create_room(rooms_uids[i], L_FIELD_WIDTH, room_click), FALSE, FALSE, 0);
    
    free(rooms_uids);
}
