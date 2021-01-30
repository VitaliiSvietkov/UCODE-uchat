#include "../../inc/uchat_client.h"

// Initialize database, if it does not exist.
void mx_database_init(void) {
    sqlite3 *db = mx_opening_db("test");
    int exit = 0;
    char *message_error;
    char *sql = "CREATE TABLE IF NOT EXISTS USERS("
        "ID          INTEGER,"
        "NAME        TEXT NOT NULL, "
        "SURENAME    TEXT NOT NULL, "
        "PSEUDONIM   TEXT NOT NULL, "
        "DESCRIPTION TEXT NOT NULL, "
        "PASSWORD    TEXT NOT NULL, "
        "LANGUAGE    INTEGER, "
        "THEME       INTEGER, "
        "PHOTO       BLOB);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Error to create USERS table");
    sql = "CREATE TABLE IF NOT EXISTS Messages(id BIGINT, \
           addresser BIGINT, destination BIGINT, Text TEXT, \
           Image BLOB, time BIGINT);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Error to create Messages table");
    sqlite3_close(db);

    int status = sqlite3_open("client/data/messages.db", &db);
    if (status != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
        sqlite3_close(db);
        return;
    }
    sqlite3_exec(db,
                "CREATE TABLE IF NOT EXISTS Messages(id BIGINT, uid BIGINT, Text TEXT, Image BLOB);",
                0, 0, &message_error);
    sqlite3_close(db);       
}
