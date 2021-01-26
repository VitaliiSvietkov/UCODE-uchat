#include "../inc/server.h"

void mx_get_avatar(char **data, int sockfd) {
    // Read from Data Base
    //======================================================
    FILE *fp = fopen("server/data/tmp_avatar.png", "wb");
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");
    
    sqlite3 *db = mx_opening_db();
    char sql[500];
    bzero(sql, 500);
    sprintf(sql, "SELECT PHOTO FROM USERS WHERE ID='%d';", mx_atoi(data[1]));
    sqlite3_stmt *pStmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    } 
    rc = sqlite3_step(pStmt);

    int bytes = 0;
    if (rc == SQLITE_ROW)
        bytes = sqlite3_column_bytes(pStmt, 0);

    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);
    send(sockfd, &bytes, sizeof(int), 0);

    if (ferror(fp))         
        fprintf(stderr, "fwrite() failed\n");    

    sqlite3_finalize(pStmt);   
    sqlite3_close(db);

    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
    //======================================================

    fp = fopen("server/data/tmp_avatar.png", "rb");

    // Get the length of the file data - 'flen'
    //======================================================
    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");          
        }    
    }  

    int flen = ftell(fp);
    if (flen == -1) {
        perror("error occurred");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }   
    }

    send(sockfd, &flen, sizeof(int), 0);

    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================

    // Get the data of the file which will be sent to client
    //======================================================
    char read_data[flen + 1];
    int size = fread(read_data, 1, flen, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    //======================================================

    send(sockfd, read_data, flen, 0);

    r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");

    remove("server/data/tmp_avatar.png");
}
