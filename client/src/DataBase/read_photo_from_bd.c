#include "../../inc/uchat_client.h"

void mx_read_photo_from_bd(int id) {
    FILE *fp = fopen("client/img/tmp_avatar.png", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char sendBuff[256];
    sprintf(sendBuff, "GetAvatar\n%d", id);
    send(sockfd, sendBuff, 256, 0);

    long flen = 0;
    recv(sockfd, &flen, sizeof(long), 0);

    char file_data[flen + 1];
    ssize_t recv_size = 0;
    while (recv_size < flen) {
        ssize_t n = recv(sockfd, file_data, flen, 0);
        recv_size += n;
    }

    //printf("%lu\n", flen);
    //printf("zd\n", recv_size);

    fwrite(file_data, flen, 1, fp);
    if (ferror(fp))
        fprintf(stderr, "fwrite() failed\n");    
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
}
