#pragma once

#include <sqlite3.h>

#include "../../libraries/include/cJSON.h"
#include "../../libraries/include/sqlite3.h"

//creation database and stuff
sqlite3 *mx_opening_db(void);
void mx_database_init(void);

void mx_create_table_users(sqlite3 *db);
//void mx_create_table_users(sqlite3 *db);
//void mx_create_table_users(sqlite3 *db);

//storing data
void mx_add_user_data(char* name, char* surename, char *pseudo, char* description);

//errors
void mx_dberror(sqlite3 *db, int status, char *msg);

//photos
void mx_read_photo_from_bd(void);
void mx_write_photo_to_bd(char *path);

//free memories

//search

//messages

//contacts

//edits

//delete

//language
void mx_write_language_data_from_bd(void);
