#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <sqlite3.h>

#include "../../libraries/libmx/inc/libmx.h"
#include "tools.h"

// Window size
//==========================================================================================
#define WIN_WIDTH_MIN 915
#define WIN_HEIGHT_MIN 680
gint CUR_WIDTH;
gint CUR_HEIGHT;
gint L_FIELD_WIDTH;
//==========================================================================================

// Colors
//==========================================================================================
// Standard ones
#define MX_1F1F1F 0.12
#define MX_E1E1E1 0.89
// Colorful theme

//==========================================================================================

// A message
//==========================================================================================
typedef struct s_message
{
    GdkPixbuf *image;
    char *text;
    int usr_id;
}              t_message;

GtkWidget *mx_create_message(t_message *data);
void mx_add_message(GtkWidget *container, t_message *message);
//==========================================================================================

// Images
//==========================================================================================
typedef struct s_img_button
{
    bool active;
    GtkWidget *box;
} t_img_button;

t_img_button add_image;
t_img_button ban_image;
t_img_button tick_image;
t_img_button more_image;

t_img_button edit_user_image;
t_img_button account_settings_image;
t_img_button change_account_image;
t_img_button chat_settings_image;
t_img_button language_image;

t_img_button settings_image;
t_img_button contacts_image;
t_img_button messages_image;
t_img_button *t_active_image;

void mx_load_images(void);
//==========================================================================================

// Log in/Registration menu
//==========================================================================================
GtkWidget *log_in_menu;
GtkWidget *authorization_container;
GtkWidget *registration_menu_1;
GtkWidget *registration_menu_2;
GtkWidget *login;
GtkWidget *password; 
GtkWidget *login_reg;
GtkWidget *password_reg;
GtkWidget *password_reg_confirm;
GtkWidget *firstname_reg;
GtkWidget *secondname_reg;
GtkWidget *login_btn;
GtkWidget *next_btn;

void mx_create_registration_menu(void);

void activate_prelight_with_condition_entry(GtkWidget *widget, GdkEvent *event, gpointer *entry);
void deactivate_prelight_with_condition_entry(GtkWidget *widget, GdkEvent *event, gpointer *entry);
void authorization_close(GtkWidget *widget, GdkEventButton *event);
void password_entry_change(GtkWidget *widget);

void button_shine(GtkWidget *widget, GdkEvent *event);
void login_btn_enter_notify(void);
void login_btn_leave_notify(void);
void hide_authorization_click(GtkWidget *widget, GdkEvent *event, gpointer *data);
void hide_registration_click(GtkWidget *widget, GdkEvent *event, gpointer *data);
void next_btn_enter_notify(GtkWidget *widget, GdkEvent *event, gpointer *data);
void next_btn_leave_notify(GtkWidget *widget, GdkEvent *event, gpointer *data);
void data_change_registration_event(GtkWidget *widget, GdkEvent *event);
void transition_registration_click(GtkWidget *widget, GdkEvent *event, gpointer *data);
void hide_registration_click_2(GtkWidget *widget, GdkEvent *event, gpointer *data);

void data_change_registration_event_2(GtkWidget *widget, gpointer data);
void authorization_after_registration(GtkWidget *widget, GdkEvent *event, gpointer *data);
void authorization(GtkWidget *widget, GdkEvent *event, gpointer *data);
void eye_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data);
//==========================================================================================


// User info
//==========================================================================================
struct
{
    int id;
    char *FirstName;
    char *SecondName;
    char *pseudonim;
    char *description;
    GdkPixbuf *avatar;
    char *password;
} t_user;

void mx_change_user_name(char fName[], char sName[]);
void mx_change_user_pseudonim(char str[]);
void mx_change_user_description(char str[]);
void mx_change_user_avatar(char path[]);
void mx_init_user(void);
//==========================================================================================


// Edit user form
//==========================================================================================
GtkWidget *edit_user_form;
GtkWidget *edit_user_main_screen;

GtkWidget *username;
GtkWidget *user_pseudonim;

GtkWidget *edit_username_label;
GtkWidget *edit_pseudo_label;

// Variables that will replace old ones
char *NewFirstName;
char *NewSecondName;
char *NewPseudonim;
char *NewDescription;
GdkPixbuf *NewAvatar;

// Edit username screen
GtkWidget *edit_username_event_screen;
GtkWidget *edit_username_eventbox;
GtkWidget *edit_username_icon;
GtkWidget *change_fname_entry;
GtkWidget *change_sname_entry;

// Edit pseudonim screen
GtkWidget *edit_pseudonim_event_screen;
GtkWidget *edit_pseudo_eventbox;
GtkWidget *edit_pseudo_icon;
GtkWidget *change_pseudo_entry;

void mx_create_edit_user_form(void);

void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event);

void edit_eventbox_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void edit_username_eventbox_enter_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void edit_username_eventbox_leave_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void fname_entry_changed_event(GtkWidget *widget);
void return_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);
void commit_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void edit_pseudo_eventbox_enter_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void edit_pseudo_eventbox_leave_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void pseudo_entry_changed_event(GtkWidget *widget);
void return_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);
void commit_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void change_description_entry_change_event(GtkWidget *widget);

void commit_edit_user_click_event(GtkWidget *widget, GdkEventButton *event);
//==========================================================================================

// Account settings form
//==========================================================================================
void mx_create_account_settings_form(void);

//==========================================================================================

// Language
//==========================================================================================
GtkWidget *mx_language_create_box(char *path, char *name);
void mx_create_language_menu(void);
void mx_language_eventbox_click(GtkWidget *widget, GdkEventButton *event, char *name);
void mx_language_close(GtkWidget *widget, GdkEventButton *event);
//==========================================================================================


void mx_init_window(void);
void mx_init_global_vars(void);

void mx_configure_main_area(void);
void mx_configure_left_header(void);
void mx_configure_content_selection_area(void);
void mx_create_message_enter_area(void);
void mx_configure_settings_menu_area(void);
void mx_configure_username_event_screen(void);
void mx_configure_pseudonim_event_screen(void);
void mx_tooltip(char *str, void *data);

// Draw functions
//==========================================================================================
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_authorization_container(GtkWidget *widget, cairo_t *cr);
gboolean mx_draw_event_message_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_delimiter(GtkWidget *widget, cairo_t *cr);
gboolean mx_draw_event_image_avatar(GtkWidget *widget, cairo_t *cr, GdkPixbuf **img_data);
gboolean mx_draw_event_round_image(GtkWidget *widget, cairo_t *cr, GdkPixbuf **img_data);
//==========================================================================================

// Event callback functions
//==========================================================================================
void image_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data);
void activate_prelight(GtkWidget *widget);
void deactivate_prelight(GtkWidget *widget);
void close_image_click_event(GtkWidget *widget, GdkEventButton *event);

void messages_click(GtkWidget *widget, GdkEventButton *event);
void contacts_click(GtkWidget *widget, GdkEventButton *event);
void settings_click(GtkWidget *widget, GdkEventButton *event);

void edit_user_enter_notify(GtkWidget *widget);
void edit_user_leave_notify(GtkWidget *widget);
void edit_user_click(GtkWidget *widget, GdkEventButton *event);

void account_settings_enter_notify(GtkWidget *widget);
void account_settings_leave_notify(GtkWidget *widget);
void account_settings_click(GtkWidget *widget, GdkEventButton *event);

void change_account_enter_notify(GtkWidget *widget);
void change_account_leave_notify(GtkWidget *widget);
void change_account_click(GtkWidget *widget, GdkEventButton *event);

void chat_settings_enter_notify(GtkWidget *widget);
void chat_settings_leave_notify(GtkWidget *widget);

void language_enter_notify(GtkWidget *widget);
void language_leave_notify(GtkWidget *widget);
void language_click(GtkWidget *widget, GdkEventButton *event);

void blackout_destroy(GtkWidget *widget, GdkEventButton *event, GtkWidget *box);
//==========================================================================================

GtkWidget *window;                      // a top-level window
GtkWidget *main_area;                   // an area that contains area with authorization form and chat area
GtkWidget *authorization_area;
GtkWidget *chat_area;

GtkWidget *entry_search;
GtkWidget *messages_box;

GtkWidget *chats_list;                  
GtkWidget *contacts_list;
GtkWidget *settings_menu;
GtkWidget *active_leftbar_container;

GtkWidget *right_container;
GtkWidget *message_enter_area;

GtkWidget *blackout;

int language;
char **text_for_labels;

// Chat room
//==========================================================================================
GtkWidget *mx_create_room(int id);
void room_click(GtkWidget *widget, GdkEventButton *event);
void room_close(GtkWidget *widget, GdkEventKey *event);
void mx_create_messages_area(void);
void mx_attach(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry);
void mx_attach_send_message_on_enter(GtkWidget *widget, char *filename);
void mx_create_attach_form(GtkWidget *entry, char *filename);
void mx_send_message(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry);
void mx_send_message_on_enter(GtkWidget *widget);
void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event);
//==========================================================================================





// DATA BASE
//==========================================================================================
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
//==========================================================================================


int mx_write_user_data_from_bd_after_auth(const char *pseudo, const char* password);
int mx_check_login_reg(const char *pseudo);


#endif
