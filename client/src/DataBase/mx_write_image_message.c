#include "../../inc/uchat_client.h"
#include "../../inc/base64.h"

typedef struct s_tmp_data
{
    char *path;
    uintptr_t id;
}              t_tmp_data;

static void *write_image_to_message(void *data);

void mx_write_image_message(char *path, unsigned int id) {
    t_tmp_data *data = (t_tmp_data *)malloc(sizeof(t_tmp_data));
    data->id = (uintptr_t)id;
    data->path = mx_strdup(path);
    pthread_t write_to_message;
    pthread_create(&write_to_message, NULL, write_image_to_message, (void *)data);
}

static void *write_image_to_message(void *data) {
    mx_connect_to_server(&sock_for_send);

    char *path = (char *)(((t_tmp_data *)data)->path);
    unsigned int id = (unsigned int)(((t_tmp_data *)data)->id);
    
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
    //======================================================

    // Get the data of the file which will be sent to server
    //======================================================
    unsigned char read_data[flen + 1];
    fread(read_data, flen, 1, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================

    /*unsigned int out_size = b64e_size(flen) + 1;
    unsigned char *out_b64 = malloc( (sizeof(char) * out_size) );
    out_size = b64_encode(read_data, sizeof(read_data) / sizeof(read_data[0]), out_b64);

    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "AddImageMessage\n%d\n%d\n%d\n%u", t_user.id, (int)curr_destination, (int)id, out_size);
    send(sock_for_send, sendBuff, 256, 0);
    
    usleep(100000);
    unsigned int total = 0;
    while (total < out_size) {
        ssize_t nb = send(sock_for_send, out_b64, out_size, 0);
        total += nb;
    }

    free(out_b64);*/



    unsigned int out_size = b64e_size(flen) + 1;
    unsigned char *out_b64 = malloc( (sizeof(char) * out_size) );
    b64_encode(read_data, flen, out_b64);

    int len_encoded = strlen((char *)out_b64);

    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "AddImageMessage\n%d\n%d\n%d\n%u\n%d", t_user.id, (int)curr_destination, 
        (int)id, out_size, len_encoded);
    send(sock_for_send, sendBuff, 256, 0);

    //usleep(300000);
    int total = 0;
    while (total < len_encoded) {
        ssize_t nb = send(sock_for_send, out_b64, len_encoded, 0);
        //usleep(100000);
        total += nb;
    }

    printf("%s\n%u\n%d\n", out_b64, out_size, len_encoded);

    free(out_b64);



    r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    free(((t_tmp_data *)data)->path);
    free((t_tmp_data *)data);

    sleep(3);
    close(sock_for_send);

    return NULL;
}
