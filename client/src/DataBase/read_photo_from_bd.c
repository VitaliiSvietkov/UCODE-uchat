#include "../../inc/uchat_client.h"

void mx_read_photo_from_bd(int id) {
    
    FILE *fp = fopen("client/img/avatar2.jpg", "wb");
    
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");    
    }    
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("client/data/test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    
    char sql[500];
    bzero(sql, 500);
    sprintf(sql, "SELECT PHOTO FROM USERS WHERE ID = '%d';", id);
        
    sqlite3_stmt *pStmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to prepare statement\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        
        sqlite3_close(db);
    } 
    
    rc = sqlite3_step(pStmt);
    
    int bytes = 0;
    
    if (rc == SQLITE_ROW) {

        bytes = sqlite3_column_bytes(pStmt, 0);
    }
        
    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);

    if (ferror(fp)) {            
        
        fprintf(stderr, "fwrite() failed\n");    
    }  
    
    int r = fclose(fp);

    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }       
    
    rc = sqlite3_finalize(pStmt);   

    sqlite3_close(db);
}
