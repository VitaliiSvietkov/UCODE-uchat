#include "../../inc/server.h"

void mx_write_photo_to_bd(char *path){
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");    
    }     
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
    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    char data[flen+1];
    int size = fread(data, 1, flen, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }    
    }
    int r = fclose(fp);
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }    
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("client/data/test.db", &db);
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sqlite3_stmt *pStmt;
    char *sql = "UPDATE USERS SET PHOTO = ?;";
    
    rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    }    
    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);    
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE) {
        printf("execution failed: %s", sqlite3_errmsg(db));
    }  
    sqlite3_finalize(pStmt);    

    sqlite3_close(db);
}
