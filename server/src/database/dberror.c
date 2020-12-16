#include "../../inc/server.h"
/*
 * Checks status of sqlite requests.
 * In case of error, prints error msg.
 * Frees memory, closes db and exits program.
 */
void mx_dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        mx_write_to_log(msg, 2);
        sqlite3_free(msg);
        sqlite3_close(db); 
        exit(1);
    }
}
