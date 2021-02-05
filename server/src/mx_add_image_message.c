#include "../inc/server.h"
#include "../inc/base64.h"

void mx_add_image_message(char **data, int sockfd) {
    int uid = mx_atoi(data[1]);
    int dst = mx_atoi(data[2]);
    int m_id = mx_atoi(data[3]);

    FILE *fp = fopen("server/data/tmp_msg_image.png", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char *eptr;
    unsigned int out_size = (unsigned)strtol(data[4], &eptr, 10);

    int len_encoded = mx_atoi(data[5]);
    
    unsigned char *encoded = malloc( (sizeof(char) * out_size) );
    int recv_len = 0;
    usleep(70000);
    while (recv_len < len_encoded) {
        ssize_t n = recv(sockfd, encoded, len_encoded, 0);
        if (n <= 0)
            continue;//usleep(100000);
        else
            recv_len += n;
    }

    printf("%s\n%u\n%d\n", encoded, out_size, len_encoded);

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

    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *pStmt;
    char sql[flen + 250];
    bzero(sql, flen + 250);
    sprintf(sql, "UPDATE Messages SET Image = ? WHERE id=%d AND\
            ((addresser=%d OR addresser=%d) AND (destination=%d OR destination=%d));",
            m_id, uid, dst, uid, dst);
    
    int rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK)
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));

    sqlite3_bind_blob(pStmt, 1, decoded, flen, SQLITE_STATIC);
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE)
        printf("execution failed: %s", sqlite3_errmsg(db));

    sqlite3_finalize(pStmt);  
    sqlite3_close(db);

    free(decoded);
    //remove("server/data/tmp_msg_image.png");
}
