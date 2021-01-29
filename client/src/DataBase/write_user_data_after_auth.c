#include "../../inc/uchat_client.h"

/*
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
}*/


/*
    user_recv_data[0] - Status (SUCCESS or FAIL)
    user_recv_data[1] - ID
    user_recv_data[2] - NAME
    user_recv_data[3] - SURNAME
    user_recv_data[4] - PSEUDONIM
    user_recv_data[5] - DESCRIPTION
*/

int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* passwd) {
    if (sockfd == -1)
        mx_connect_to_server();

    char sendBuffer[1025];
    bzero(sendBuffer, 1025);
    sprintf(sendBuffer, "Authorization\n%s\n%s", pseudo, passwd);

    /*char c;
    if (recv(sockfd, &c, 1, 0) < 0) {
        perror("ERROR writing to socket");
        close(sockfd);
        sockfd = -1;
        return 1;
    }*/

    /*int error = 0;
    socklen_t len = sizeof (error);
    int retval = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
    if (retval != 0) {
        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
        return 1;
    }
    if (error != 0) {
        fprintf(stderr, "socket error: %s\n", strerror(error));
    }*/

    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) <= 0) {
         perror("ERROR writing to socket");
         //close(sockfd);
         return 1;
    }
    char recvBuffer[6000];
    bzero(recvBuffer, 6000);
    if (recv(sockfd, recvBuffer, 6000, 0) < 0) {
         perror("ERROR reading from socket");
    }

    char **user_recv_data = mx_strsplit(recvBuffer, '\n');
    if (!mx_strcmp(user_recv_data[0], "SUCCESS")) {
        t_user.id = mx_atoi(user_recv_data[1]);

        if (t_user.FirstName != NULL)
            free(t_user.FirstName);
        t_user.FirstName = mx_strdup(user_recv_data[2]);

        if (t_user.SecondName != NULL)
            free(t_user.SecondName);
        t_user.SecondName = mx_strdup(user_recv_data[3]);

        if (t_user.pseudonim != NULL)
            free(t_user.pseudonim);
        t_user.pseudonim = mx_strdup(user_recv_data[4]);

        if (t_user.description != NULL)
            free(t_user.description);
        t_user.description = mx_strdup(user_recv_data[5]);

        if (t_user.avatar != NULL)
            g_object_unref(t_user.avatar);
            
        //mx_read_photo_from_bd(t_user.id);
        t_user.avatar = mx_get_pixbuf_with_size("client/img/ukraine.png", 100, 100);
        //remove("client/img/tmp_avatar.png");
        //==========================================================================
        mx_del_strarr(&user_recv_data);
    }
    else {
        printf("%s\n", recvBuffer);
        mx_del_strarr(&user_recv_data);
        return 1; 
    }
    return 0;
}

int mx_check_login_reg(const char *pseudo) {
    char sendBuffer[1024];
    bzero(sendBuffer, 1024);
    sprintf(sendBuffer, "FindUser\n%s", pseudo);
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }

    char recvBuffer[1024];
    bzero(recvBuffer, 1024);
    if (recv(sockfd, recvBuffer, 1024, 0) < 0) {
         perror("ERROR reading from socket");
    }
    
    if (!mx_strcmp(recvBuffer, "FAIL"))
        return 0;
    else
        return 1;
}
