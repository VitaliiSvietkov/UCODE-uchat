#include "../../inc/server.h"

void mx_add_user_data(char* name, char* surename, char *pseudo, char* description) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT NAME, SURENAME, PSEUDONIM, DESCRIPTION FROM USERS;");
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
    if(mx_strcmp(check_name, name) == 0 && mx_strcmp(check_sname, surename) == 0 && mx_strcmp(check_pseudo, pseudo) == 0 && mx_strcmp(check_description, description) == 0){
        mx_write_to_log("User exist", 2);
        sqlite3_close(db);
    }
    else { 
    sprintf(sql, 
            "INSERT OR REPLACE INTO USERS (NAME, SURENAME, PSEUDONIM, DESCRIPTION) VALUES('%s','%s', '%s', '%s');", 
            name, surename, pseudo, description);   
    st = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    mx_dberror(db, st, errmsg); 
    }    
}
