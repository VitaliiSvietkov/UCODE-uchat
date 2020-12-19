#include "../../inc/database.h"
/*
Opens db, or creates new.
In case, it cannot be open,
Prints error msg and exits program.
*/
sqlite3 *mx_opening_db(char *name_db) {
    sqlite3 *db;

    if (sqlite3_open(name_db, &db) != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
            sqlite3_errmsg(db);
    }
    mx_create_table(db);
return db;
}
