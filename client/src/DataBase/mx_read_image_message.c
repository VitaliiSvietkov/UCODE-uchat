#include "../../inc/uchat_client.h"
#include "../../inc/base64.h"

GdkPixbuf *mx_read_image_message(int id) {
    mx_connect_to_server(&sock_for_send);

    char sendBuff[256];
    bzero(sendBuff, 256);
    sprintf(sendBuff, "GetMessageImage\n%d\n%d\n%d", id, t_user.id, (int)curr_destination);
    send(sock_for_send, sendBuff, 256, 0);

    int bytes = 0;
    recv(sock_for_send, &bytes, sizeof(int), 0);
    
    if (bytes) {
        FILE *fp = fopen("client/img/message_image_temp.png", "wb");
        if (fp == NULL)
            fprintf(stderr, "Cannot open image file\n");

        int len_encoded = 0;
        recv(sock_for_send, &len_encoded, sizeof(int), 0);

        unsigned char *encoded = malloc( (sizeof(char) * len_encoded) );
        mx_memset(encoded, 0, len_encoded);
        mx_recv_all(&sock_for_send, &encoded, len_encoded);

        unsigned int flen = b64d_size(len_encoded);
        unsigned char *decoded = malloc( (sizeof(char) * flen) + 1);
        flen = b64_decode(encoded, len_encoded, decoded);        
        free(encoded);

        fwrite(decoded, flen, 1, fp);
        if (ferror(fp))
            fprintf(stderr, "fwrite() failed\n");
        
        int r = fclose(fp);
        if (r == EOF)
            fprintf(stderr, "Cannot close file handler\n");

        free(decoded);

        GdkPixbuf *result = mx_create_pixbuf("client/img/message_image_temp.png");
        result = mx_size_image_down(result);
        remove("client/img/message_image_temp.png");
        close(sock_for_send);
        return result;
    }
    close(sock_for_send);
    return NULL;
}
