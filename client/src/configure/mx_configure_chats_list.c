#include "../../inc/uchat_client.h"

void mx_configure_chats_list(void) {
    if (sockfd == -1){
        mx_connect_to_server();
        //return 1;
    }
    chats_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), chats_list, 0, 105);

    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "GetUsersArr\n%d", t_user.id);

    int error = 0;
    socklen_t len = sizeof (error);
    int retval = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
    if (retval != 0) {
        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
        sockfd = -1;
        return;
    }
    if (error != 0) {
        fprintf(stderr, "socket error: %s\n", strerror(error));
        sockfd = -1;
         return;
    }

    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) == -1) {
        perror("ERROR writing to socket");
        pthread_t thread_id;
        char *err_msg = "Connection lost\nTry again later";
        pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
        sockfd = -1;
        return;
    }
    
    int rooms_uids_len = 0;
    
    if(recv(sockfd, &rooms_uids_len, sizeof(int), 0) == 0){
        pthread_t thread_id;
        char *err_msg = "Connection lost\nTry again later";
        pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
        sockfd = -1;
        return;
    }



    unsigned int *rooms_uids = (unsigned int *)malloc(rooms_uids_len);
    for (int i = 0; i < rooms_uids_len; i++)
        if(recv(sockfd, &rooms_uids[i], sizeof(unsigned int), 0) == 0){
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            sockfd = -1;
            return;
        }
    
    for (int i = 0; i < rooms_uids_len; i++)
        gtk_box_pack_start(GTK_BOX(chats_list), 
            mx_create_room(rooms_uids[i], L_FIELD_WIDTH, room_click), FALSE, FALSE, 0);
    
    free(rooms_uids);
}
