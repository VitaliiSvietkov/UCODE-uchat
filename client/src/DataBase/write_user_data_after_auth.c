#include "../../inc/uchat_client.h"

int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* passwd) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (sqlite3_step(res) != SQLITE_DONE) {
        char *check_password = mx_strdup((char *)sqlite3_column_text(res, 0));
        if (mx_strcmp(check_password, passwd) == 0) {
            sqlite3_finalize(res);
            sprintf(sql, "SELECT ID, NAME, SURENAME, PSEUDONIM, DESCRIPTION FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
            sqlite3_prepare_v2(db, sql, -1, &res, 0);
            sqlite3_step(res);
            int newId = (int)sqlite3_column_int(res, 0);
            t_user.id = newId;
            char *newName = mx_string_copy((char *)sqlite3_column_text(res, 1));
            if (t_user.FirstName != NULL)
                free(t_user.FirstName);
            t_user.FirstName = newName;
            char *newSName = mx_string_copy((char *)sqlite3_column_text(res, 2));
            if (t_user.SecondName != NULL)
                free(t_user.SecondName);
            t_user.SecondName = newSName;
            char *newPseudo = mx_string_copy((char *)sqlite3_column_text(res, 3));
            if (t_user.pseudonim != NULL)
                free(t_user.pseudonim);
            t_user.pseudonim = newPseudo;
            char *newDescr = mx_string_copy((char *)sqlite3_column_text(res, 4));
            if (t_user.description != NULL)
                free(t_user.description);
            t_user.description = newDescr;
            char *newPass = check_password;
            if (t_user.password != NULL)
                free(t_user.password);
            t_user.password = newPass;
            mx_read_photo_from_bd(newId);
            if (t_user.avatar != NULL)
                g_object_unref(t_user.avatar);
            t_user.avatar = mx_get_pixbuf_with_size("client/img/avatar2.jpg", 100, 100);
        }
        else {
            free(check_password);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return 1; 
        }
        sqlite3_finalize(res);
    }
    else {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return 1; 
    }
    sqlite3_close(db);
    return 0;
}

int mx_check_login_reg(const char *pseudo) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (sqlite3_step(res) != SQLITE_DONE) {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return 0;
}

/*
int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* passwd) {
    char sendBuffer[1025];
    bzero(sendBuffer, 1025);
    sprintf(sendBuffer, "Authorization\n%s\n%s", pseudo, passwd);
    printf("Before send\n");
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }
    printf("Before recv\n");
    char recvBuffer[1024];
    bzero(recvBuffer, 1024);
    if (recv(sockfd, recvBuffer, sizeof(recvBuffer), 0) < 0) {
         perror("ERROR reading from socket");
    }
    printf("Before strcmp\n");


    if (!mx_strcmp(recvBuffer, "SUCCESS")) {
        int newId = (int)sqlite3_column_int(res, 0);
        t_user.id = newId;
        char *newName = mx_string_copy((char *)sqlite3_column_text(res, 1));
        if (t_user.FirstName != NULL)
            free(t_user.FirstName);
        t_user.FirstName = newName;
        char *newSName = mx_string_copy((char *)sqlite3_column_text(res, 2));
        if (t_user.SecondName != NULL)
            free(t_user.SecondName);
        t_user.SecondName = newSName;
        char *newPseudo = mx_string_copy((char *)sqlite3_column_text(res, 3));
        if (t_user.pseudonim != NULL)
            free(t_user.pseudonim);
        t_user.pseudonim = newPseudo;
        char *newDescr = mx_string_copy((char *)sqlite3_column_text(res, 4));
        if (t_user.description != NULL)
            free(t_user.description);
        t_user.description = newDescr;
        char *newPass = check_password;
        if (t_user.password != NULL)
            free(t_user.password);
        t_user.password = newPass;
        mx_read_photo_from_bd(newId);
        if (t_user.avatar != NULL)
            g_object_unref(t_user.avatar);
        t_user.avatar = mx_get_pixbuf_with_size("client/img/avatar2.jpg", 100, 100);
    }
    else {
        printf("%s\n", recvBuffer);
        return 1; 
    }
    return 0;
}

int mx_check_login_reg(const char *pseudo) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE PSEUDONIM = '%s';", pseudo);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (sqlite3_step(res) != SQLITE_DONE) {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return 0;
}
*/
