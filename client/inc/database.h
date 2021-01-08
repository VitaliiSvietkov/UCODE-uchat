#ifndef CLIENT_DB
#define CLIENT_DB

#include <sqlite3.h>

//int mx_create_db(const char* s); 
//int mx_create_table(const char* s);
void mx_write_to_log(char *msg, int stream);

sqlite3 *mx_opening_db(void);
void mx_dberror(sqlite3 *db, int status, char *msg);
void mx_database_init(void);
void mx_add_user_data(const char *pseudo, const char *password, const char *name, const char *sname);
void mx_read_photo_from_bd(void);
void mx_write_language_data_from_bd(void);
void mx_write_photo_to_bd(char *path);



char *mx_string_copy(char *str);
void mx_write_user_data_from_bd(void);
void mx_edit_name(char* name, char* surname, char* pseudo, char *description, int id);
void mx_edit_language(int language);
//void mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* password);


int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* password);
int mx_check_login_reg(const char *pseudo);

#endif
