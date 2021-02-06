#include "../inc/server.h"
#include "../inc/base64.h"

static void recv_all(int *socket, unsigned char **buffer, size_t length);

void mx_update_avatar(char **data, int sockfd) {
    FILE *fp = fopen("server/data/tmp_recv_avatar.png", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    int len_encoded = 0;
    recv(sockfd, &len_encoded, sizeof(int), 0);

    unsigned char *encoded = malloc(len_encoded);
    mx_memset(encoded, 0, len_encoded);
    recv_all(&sockfd, &encoded, len_encoded);

    printf("%s\n%d\n%d\n", encoded, len_encoded, mx_strlen((char *)encoded));

    unsigned int flen = b64d_size(len_encoded);
    unsigned char *decoded = malloc( (sizeof(char) * flen) );
    memset(decoded, 0, flen);
    flen = b64_decode(encoded, len_encoded, decoded);
    free(encoded);

    fwrite(decoded, flen, 1, fp);
    if (ferror(fp))
        fprintf(stderr, "fwrite() failed\n");
    free(decoded);
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    return;
    
    /*
    fp = fopen("server/data/tmp_recv_avatar.png", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");    
    }    

    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");          
        }    
    }  

    flen = ftell(fp);
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

    char read_data[flen + 1];
    fread(read_data, flen, 1, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }

    r = fclose(fp);
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }    

    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *pStmt;
    char sql[flen + 40];
    bzero(sql, flen + 40);
    sprintf(sql, "UPDATE USERS SET PHOTO = ? WHERE ID=%d;", mx_atoi(data[1]));
    
    int rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK)
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_bind_blob(pStmt, 1, read_data, flen, SQLITE_STATIC);
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE)
        printf("execution failed: %s", sqlite3_errmsg(db));
    sqlite3_finalize(pStmt);    
    sqlite3_close(db);

    remove("server/data/tmp_recv_avatar.png");
    */
}

static void recv_all(int *socket, unsigned char **buffer, size_t length) {
    unsigned char *ptr = *buffer;
    while (length > 0) {
        int i = recv(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
    //printf("%s\n", ptr);
}
