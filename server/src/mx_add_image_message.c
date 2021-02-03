#include "../inc/server.h"

void mx_add_image_message(char **data, int sockfd) {
    int uid = mx_atoi(data[1]);
    int dst = mx_atoi(data[2]);
    int m_id = mx_atoi(data[3]);

    FILE *fp = fopen("server/data/tmp_msg_image.png", "ab");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char *eptr;
    long flen = strtol(data[4], &eptr, 10);

    long recv_len = 0;
    char file_data[2];
    while (recv_len < flen) {
        bzero(file_data, 2);
        ssize_t total_recv = 0;
        ssize_t n = 0;
        while (total_recv < 2) {
            n = recv(sockfd, file_data, 2, 0);
            recv_len += n;
            total_recv += n;
        }
        fwrite(file_data, 2, 1, fp);
        if (ferror(fp)) {
            fprintf(stderr, "fwrite() failed\n");
            break;
        }
    }
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    return;

    // Read from the file and add to db
    fp = fopen("server/data/tmp_msg_image.png", "rb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");    

    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        r = fclose(fp);
        if (r == EOF)
            fprintf(stderr, "Cannot close file handler\n");          
    }  

    char read_data[flen + 1];
    int size = fread(read_data, flen, 1, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        r = fclose(fp);
        if (r == EOF)
            fprintf(stderr, "Cannot close file handler\n");
    }

    r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *pStmt;
    char sql[flen + 250];
    bzero(sql, flen + 250);
    sprintf(sql, "UPDATE Messages SET Image=? WHERE id=%d AND\
            ((addresser=%d OR addresser=%d) AND (destination=%d OR destination=%d));",
            m_id, uid, dst, uid, dst);
    
    int rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK)
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));

    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);    
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE)
        printf("execution failed: %s", sqlite3_errmsg(db));

    sqlite3_finalize(pStmt);  
    sqlite3_close(db);

    remove("server/data/tmp_recv_avatar.png");
}
