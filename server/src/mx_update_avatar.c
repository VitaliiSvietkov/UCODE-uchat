#include "../inc/server.h"

void mx_update_avatar(char **data, int sockfd) {
    FILE *fp = fopen("server/data/tmp_recv_avatar.png", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    long flen = 0;
    recv(sockfd, &flen, sizeof(long), 0);

    char file_data[flen + 1];
    recv(sockfd, file_data, flen, 0);

    fwrite(file_data, flen, 1, fp);
    if (ferror(fp))
        fprintf(stderr, "fwrite() failed\n");
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    
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
    char sql[10000];
    bzero(sql, 10000);
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

    //remove("server/data/tmp_recv_avatar.jpg");
}
