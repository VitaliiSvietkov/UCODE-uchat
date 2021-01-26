#include "../../inc/uchat_client.h"

void mx_write_photo_to_bd(char *path, int id){
    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "UpdateAvatar\n%d", id);
    send(sockfd, sendBuff, 256, 0);

    FILE *fp = fopen(path, "rb");
    int r;

    // Get the length of the file data - 'flen'
    //======================================================
    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");          
        }    
    }  

    int flen = ftell(fp);
    if (flen == -1) {
        perror("error occurred");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }   
    }

    send(sockfd, &flen, sizeof(int), 0);

    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================

    // Get the data of the file which will be sent to server
    //======================================================
    char read_data[flen + 1];
    int size = fread(read_data, 1, flen, fp);
    send(sockfd, &size, sizeof(int), 0);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================

    send(sockfd, read_data, flen, 0);

    r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
}
