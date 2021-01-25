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
    
    int uid_arr_len = 0;
    unsigned int *uid_arr = NULL;
    recv(sockfd, &uid_arr_len, sizeof(int), 0);

    uid_arr = (unsigned int *)malloc(uid_arr_len);
    for (int i = 0; i < uid_arr_len; i++)
        recv(sockfd, &uid_arr[i], sizeof(unsigned int), 0);

    
    for (int i = 0; i < uid_arr_len; i++)
        gtk_box_pack_start(GTK_BOX(chats_list), 
            mx_create_room(uid_arr[i], L_FIELD_WIDTH, room_click), FALSE, FALSE, 0);
    
    free(uid_arr);
    uid_arr = NULL;
}
