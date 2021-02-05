#include "../inc/server.h"
#include "../inc/base64.h"

void mx_get_image_message(char **data, int sockfd) {
    int m_id = mx_atoi(data[1]);
    int uid = mx_atoi(data[2]);
    int dst = mx_atoi(data[3]);

    sqlite3 *db = mx_opening_db();
    char sql[200];
    bzero(sql, 200);
    sprintf(sql, "SELECT Image FROM Messages WHERE id=%d AND\
            ((addresser=%d OR addresser=%d) AND (destination=%d OR destination=%d));",
            m_id, dst, uid, dst, uid);
        
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));     
        rc = sqlite3_finalize(pStmt);
        return;
    } 
    
    rc = sqlite3_step(pStmt);
    int bytes = 0;
    if (rc == SQLITE_ROW)
        bytes = sqlite3_column_bytes(pStmt, 0);

    send(sockfd, &bytes, sizeof(int), 0);

    if (bytes) {
        const void *blob_data = sqlite3_column_blob(pStmt, 0);
        if (blob_data == NULL) {    
            rc = sqlite3_finalize(pStmt);
            return;
        }
        unsigned char *write_data = malloc(bytes + 1);
        memcpy(write_data, blob_data, bytes);
        write_data[bytes] = '\0';

        FILE *fp = fopen("server/data/message_image_temp.jpg", "wb");
        if (fp == NULL)
            fprintf(stderr, "Cannot open image file\n");

        fwrite(write_data, bytes + 1, 1, fp);
        if (ferror(fp))         
            fprintf(stderr, "fwrite() failed\n");
        
        free(write_data);
        
        int r = fclose(fp);
        if (r == EOF)
            fprintf(stderr, "Cannot close file handler\n");
        //============================================================

        fp = fopen("server/data/message_image_temp.jpg", "rb");

        fseek(fp, 0, SEEK_END);
        if (ferror(fp)) {
            fprintf(stderr, "fseek() failed\n");
            r = fclose(fp);
            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");          
            }    
        }  
        long flen = ftell(fp);
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

        unsigned char read_data[flen + 1];
        fread(read_data, flen, 1, fp);
        if (ferror(fp)) {
            fprintf(stderr, "fread() failed\n");
            r = fclose(fp);
            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");
            }    
        }

        r = fclose(fp);
        if (r == EOF)
            fprintf(stderr, "Cannot close file handler\n");
        
        remove("server/data/message_image_temp.jpg");

        unsigned int out_size = b64e_size(flen) + 1;
        send(sockfd, &out_size, sizeof(unsigned int), 0);

        unsigned char *out_b64 = malloc( (sizeof(char) * out_size) );
        b64_encode(read_data, flen, out_b64);

        int len_encoded = strlen((char *)out_b64);
        send(sockfd, &len_encoded, sizeof(int), 0);

        //usleep(300000);
        int total = 0;
        while (total < len_encoded) {
            ssize_t nb = send(sockfd, out_b64, len_encoded, 0);
            //usleep(100000);
            total += nb;
        }
        free(out_b64);

        //printf("%s\n%u\n%d\n", out_b64, out_size, total);
    }
    rc = sqlite3_finalize(pStmt); 
    sqlite3_close(db);
}
