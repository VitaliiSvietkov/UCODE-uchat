#include "../../inc/server.h"
/*
Opens db, or creates new.
In case, it cannot be open,
Prints error msg and exits program.
*/
sqlite3 *mx_opening_db(void) {
    sqlite3 *db;
    int status = sqlite3_open("client/data/test.db", &db);
    if (status != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
            sqlite3_errmsg(db);
    sqlite3_close(db); 
    exit(1);
}
