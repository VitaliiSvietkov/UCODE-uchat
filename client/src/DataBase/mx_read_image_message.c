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

        //char *eptr;
        unsigned int out_size = 0; // (unsigned)strtol(data[4], &eptr, 10);
        recv(sock_for_send, &out_size, sizeof(unsigned int), 0);

        int len_encoded = 0;
        recv(sock_for_send, &len_encoded, sizeof(int), 0);

        unsigned char *encoded = malloc( (sizeof(char) * out_size) );
        int recv_len = 0;
        usleep(70000);
        while (recv_len < len_encoded) {
            ssize_t n = recv(sock_for_send, encoded, len_encoded, 0);
            if (n <= 0)
                continue;
            else
                recv_len += n;
        }

        unsigned int flen = b64d_size(len_encoded);
        unsigned char *decoded = malloc( (sizeof(char) * flen) + 1);
        flen = b64_decode(encoded, len_encoded, decoded);

        //printf("%s\n%u\n%d\n", encoded, out_size, len_encoded);
        
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



    /*
    FILE *fp = fopen("client/img/message_image_temp.png", "wb");
    
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char sql[200];
    bzero(sql, 200);
    sprintf(sql, "SELECT Image FROM Messages WHERE id=%u AND\
            ((addresser=%u OR addresser=%u) AND (destination=%u OR destination=%u));",
            id, curr_destination, t_user.id, curr_destination, t_user.id);
        
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(data_base, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(data_base));
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }       
        rc = sqlite3_finalize(pStmt);
        
        remove("client/img/message_image_temp.png");
        return NULL;
    } 
    
    rc = sqlite3_step(pStmt);
    int bytes = 0;
    if (rc == SQLITE_ROW)
        bytes = sqlite3_column_bytes(pStmt, 0);
    
    const void *blob_data = sqlite3_column_blob(pStmt, 0);
    if (blob_data == NULL) {
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }       
        rc = sqlite3_finalize(pStmt);
        remove("client/img/message_image_temp.png");
        return NULL;
    }

    fwrite(blob_data, bytes, 1, fp);
    if (ferror(fp))         
        fprintf(stderr, "fwrite() failed\n");
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
    
    rc = sqlite3_finalize(pStmt); 

    GdkPixbuf *result = mx_create_pixbuf("client/img/message_image_temp.png");
    result = mx_size_image_down(result);
    remove("client/img/message_image_temp.png");
    return result;
    */
}
