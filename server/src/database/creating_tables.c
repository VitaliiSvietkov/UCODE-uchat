#include "../../inc/server.h"



/*
Creation tables of :
    users
    messages
    rooms
*/
void mx_create_table_users(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists users("
                           "Name          text        not null,"
                           "Pseudonim     text        not null,"
                           "Password      text        not null,"
                           "Token         text        not null,"
                           "Description   text        );"
                           "Token         text        not null,",
                0, 0, 0);
}

void mx_create_table_messages(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists messages("
                                                    ,
                 0, 0, 0);
}

void mx_create_table_rooms(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists rooms("
                                                    ,
                 0, 0, 0);
}
