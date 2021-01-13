#include "../../inc/uchat_client.h"

sqlite3 *mx_opening_db(char *filename) {
    char path[50];
    sprintf(path, "client/data/%s.db", filename);
    sqlite3 *db = NULL;
    int status = sqlite3_open(path, &db);
    if (status != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
    }
    return db;
}
