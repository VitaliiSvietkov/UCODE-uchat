#ifndef CLIENT_DB
#define CLIENT_DB

#include <sqlite3.h>
#include "tools.h"

//int mx_create_db(const char* s); 
//int mx_create_table(const char* s);
void mx_write_to_log(char *msg, int stream);

sqlite3 *mx_opening_db(void);
void mx_dberror(sqlite3 *db, int status, char *msg);
void mx_database_init(void);
void mx_add_user_data(const char *pseudo, const char *password, const char *name, const char *sname);
void mx_read_photo_from_bd(int id);
void mx_write_language_data_from_bd(void);
void mx_write_photo_to_bd(char *path, int id);

void mx_write_image_message(char *path, unsigned int id, sqlite3 *data_base);
GdkPixbuf *mx_read_image_message(unsigned int id, sqlite3 *data_base);
void mx_delete_message_from_db(t_message *data);


char *mx_string_copy(char *str);
void mx_write_user_data_from_bd(void);
void mx_edit_name(char* name, char* surname, char* pseudo, char *description, int id);
void mx_edit_language(int language);
//void mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* password);


int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* passwd);
int mx_check_login_reg(const char *pseudo);

#endif
