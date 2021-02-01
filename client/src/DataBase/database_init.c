#include "../../inc/uchat_client.h"

// Initialize database, if it does not exist.
void mx_local_database_init(void) {
    sqlite3 *db = mx_opening_local_db();
    int exit = 0;
    char *message_error;
    char *sql = "CREATE TABLE IF NOT EXISTS Messages(id BIGINT, \
           addresser BIGINT, destination BIGINT, Text TEXT, \
           Image BLOB, time BIGINT);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Error to create Messages table");
    sqlite3_close(db);
}
