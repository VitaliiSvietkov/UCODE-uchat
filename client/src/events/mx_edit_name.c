#include "../../inc/uchat_client.h"

void mx_edit_name(char* name, char* surname, char* pseudo, char *description, int id) {
    sqlite3 *db = mx_opening_db("test");
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    if (surname == NULL) {
        surname = " ";
    }
    sprintf(sql, "SELECT NAME, SURENAME, PSEUDONIM, DESCRIPTION FROM USERS WHERE ID = '%d';", id);
    char *check_name;
    char *check_sname;
    char *check_pseudo;
    char *check_description;
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    check_name = mx_string_copy((char *)sqlite3_column_text(res, 0));
    check_sname = mx_string_copy((char *)sqlite3_column_text(res, 1));
    check_pseudo = mx_string_copy((char *)sqlite3_column_text(res, 2));
    check_description = mx_string_copy((char *)sqlite3_column_text(res, 3));
    sqlite3_finalize(res);
    sprintf(sql, "UPDATE USERS SET NAME = REPLACE(NAME, '%s' ,'%s'), "
    "SURENAME = REPLACE(SURENAME, '%s', '%s'), "
    "PSEUDONIM = REPLACE(PSEUDONIM, '%s','%s'), "
    "DESCRIPTION = REPLACE(DESCRIPTION, '%s','%s') WHERE ID = '%d' ;",
    check_name, name, check_sname, surname, check_pseudo, pseudo, check_description, description, id);   
    st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
}
