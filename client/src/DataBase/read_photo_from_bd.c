#include "../../inc/uchat_client.h"

void mx_read_photo_from_bd(int id) {
    if (sockfd == -1){
        mx_connect_to_server();
        //return 1;
    }
    
    FILE *fp = fopen("client/img/tmp_avatar.png", "ab");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char sendBuff[256];
    sprintf(sendBuff, "GetAvatar\n%d", id);

    if(send(sockfd, sendBuff, 256, 0) == -1) {
        pthread_t thread_id;
        char *err_msg = "Connection lost\nTry again later";
        pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
        sockfd = -1;
        return;
    }

    long flen = 0;
    if(recv(sockfd, &flen, sizeof(long), 0) == 0) {
        pthread_t thread_id;
        char *err_msg = "Connection lost\nTry again later";
        pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
        sockfd = -1;
        return;
    }

    long recv_len = 0;
    while (recv_len < flen) {
        char file_data[6];
        ssize_t n = recv(sockfd, file_data, 6, 0);
        recv_len += n;
        fwrite(&file_data, 6, 1, fp);
        if (ferror(fp)) {
            fprintf(stderr, "fwrite() failed\n");
            break;
        }
    }
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
}
