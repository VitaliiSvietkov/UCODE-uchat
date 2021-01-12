#include "../../inc/uchat_client.h"

GdkPixbuf *mx_read_image_message(unsigned int id, sqlite3 *data_base) {
    FILE *fp = fopen("client/img/message_image_temp.jpg", "wb");
    
    if (fp == NULL)
        fprintf(stderr, "Cannot open image file\n");

    char sql[100];
    sprintf(sql, "SELECT Image FROM Messages WHERE id='%u';", id);
        
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
        
        remove("client/img/message_image_temp.jpg");
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
        remove("client/img/message_image_temp.jpg");
        return NULL;
    }

    fwrite(blob_data, bytes, 1, fp);
    if (ferror(fp))         
        fprintf(stderr, "fwrite() failed\n");
    
    int r = fclose(fp);
    if (r == EOF)
        fprintf(stderr, "Cannot close file handler\n");
    
    rc = sqlite3_finalize(pStmt); 

    GdkPixbuf *result = mx_create_pixbuf("client/img/message_image_temp.jpg");
    result = mx_size_image_down(result);
    remove("client/img/message_image_temp.jpg");
    return result;
}
