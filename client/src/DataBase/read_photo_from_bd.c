#include "../../inc/uchat_client.h"

void mx_read_photo_from_bd(int id) {
    FILE *fp = fopen("client/img/tmp_avatar.jpg", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char sendBuff[256];
    sprintf(sendBuff, "GetAvatar\n%d", id);
    send(sockfd, sendBuff, 256, 0);
    
    int bytes = 0;
    recv(sockfd, &bytes, sizeof(int), 0);

    int flen = 0;
    recv(sockfd, &flen, sizeof(int), 0);

    char *file_data = (char *)malloc(flen + 1);
    recv(sockfd, file_data, flen + 1, 0);

    fwrite(file_data, bytes, 1, fp);
    if (ferror(fp))
        fprintf(stderr, "fwrite() failed\n");    
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
    free(file_data);
}
