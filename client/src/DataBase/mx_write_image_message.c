#include "../../inc/uchat_client.h"

void mx_write_image_message(char *path, unsigned int id) {
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
    long flen = ftell(fp);
    if (flen == -1) {
        perror("error occurred");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }   
    }
    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }

    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "AddImageMessage\n%d\n%d\n%d\n%ld", t_user.id, (int)curr_destination, (int)id, flen);
    send(sockfd, sendBuff, 256, 0);

    /*if(send(sockfd, &flen, sizeof(long), 0) == -1) {
        pthread_t thread_id;
        char *err_msg = "Connection lost\nTry again later";
        pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
        sockfd = -1;
        return;
    }*/
    //======================================================

    // Get the data of the file which will be sent to server
    //======================================================
    char read_data[flen + 1];
    fread(read_data, flen, 1, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================
    
    for (long i = 0; i < flen; i += 2) {
        ssize_t total = 0;
        while (total < 2) {
            ssize_t nb = send(sockfd, &read_data[i], 2, 0);
            total += nb;
        }
    }

    r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
}
