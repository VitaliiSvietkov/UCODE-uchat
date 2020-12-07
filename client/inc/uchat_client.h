#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>

// Window size
//=========================
#define WIN_WIDTH_MIN 915
#define WIN_HEIGHT_MIN 680
gint CUR_WIDTH;
gint CUR_HEIGHT;
gint L_FIELD_WIDTH;
//=========================

// Colors
//=====================
// Standard ones
#define MX_1F1F1F 0.12
#define MX_E1E1E1 0.89
// Colorful theme

//=====================

// Images
//============================
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
t_img_button change_account_image;
t_img_button chat_settings_image;
t_img_button language_image;

t_img_button settings_image;
t_img_button contacts_image;
t_img_button messages_image;
t_img_button *t_active_image;

void mx_load_images(void);
//============================

// User info
//==========================================================================================
struct
{
    char *FirstName;
    char *SecondName;
    char *pseudonim;
    char *description;
    GdkPixbuf *avatar;
} t_user;

void mx_change_user_name(char fName[], char sName[]);
void mx_change_user_pseudonim(char str[]);
void mx_change_user_description(char str[]);
void mx_change_user_avatar(char path[]);
void mx_init_user(void);
//==========================================================================================

GtkWidget *window;
GtkWidget *main_area;

GtkWidget *chats_list;
GtkWidget *contacts_list;
GtkWidget *settings_menu;
GtkWidget *active_leftbar_container;
GtkWidget *chat_enter_area;

GtkWidget *back_blackout;

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
//==========================================================================================

void mx_init_window(GtkWidget **window);

void mx_configure_main_area(GtkWidget **background, GtkWidget **window);
void mx_configure_left_header(GtkWidget **left_header, GtkWidget **entry_search);
void mx_configure_content_selection_area(GtkWidget **content_selection_area);
void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **entry_chat);
void mx_configure_settings_menu_area(void);
void mx_create_edit_user_form(void);
void mx_configure_username_event_screen(void);
void mx_configure_pseudonim_event_screen(void);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
GdkPixbuf *mx_get_pixbuf_with_size(char *path, int w, int h);
void mx_tooltip(char *str, void *data);

// All draw functions are in "mx_draw_functions.c"
//==========================================================================================
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_delimiter(GtkWidget *widget, cairo_t *cr);
gboolean mx_draw_event_image_avatar(GtkWidget *widget, cairo_t *cr, GdkPixbuf **img_data);
//==========================================================================================

// Event callback functions (look in "mx_events.c")
//================================
void image_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data);
void image_enter_notify(GtkWidget *widget);
void image_leave_notify(GtkWidget *widget);
void close_image_click_event(GtkWidget *widget, GdkEventButton *event);

void messages_enter_notify(GtkWidget *widget);
void messages_leave_notify(GtkWidget *widget);
void messages_click(GtkWidget *widget, GdkEventButton *event);

void contacts_enter_notify(GtkWidget *widget);
void contacts_leave_notify(GtkWidget *widget);
void contacts_click(GtkWidget *widget, GdkEventButton *event);

void settings_enter_notify(GtkWidget *widget);
void settings_leave_notify(GtkWidget *widget);
void settings_click(GtkWidget *widget, GdkEventButton *event);

void add_enter_notify(GtkWidget *widget);
void add_leave_notify(GtkWidget *widget);

void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event);

void more_enter_notify(GtkWidget *widget);
void more_leave_notify(GtkWidget *widget);

void edit_user_enter_notify(GtkWidget *widget);
void edit_user_leave_notify(GtkWidget *widget);
void edit_user_click(GtkWidget *widget, GdkEventButton *event);

void change_account_enter_notify(GtkWidget *widget);
void change_account_leave_notify(GtkWidget *widget);

void chat_settings_enter_notify(GtkWidget *widget);
void chat_settings_leave_notify(GtkWidget *widget);

void language_enter_notify(GtkWidget *widget);
void language_leave_notify(GtkWidget *widget);




void blackout_leave_notify_event(void);
void blackout_click(GtkWidget *widget, GdkEventButton *event);

void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event);

void edit_eventbox_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void edit_username_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void edit_username_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void fname_entry_changed_event(GtkWidget *widget);
void return_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);
void commit_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void edit_pseudo_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void edit_pseudo_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data);
void pseudo_entry_changed_event(GtkWidget *widget);
void return_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);
void commit_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data);

void change_description_entry_change_event(GtkWidget *widget);

void commit_edit_user_click_event(GtkWidget *widget, GdkEventButton *event);
//================================

char *mx_strnew(const int size);
char *mx_strjoin(const char *s1, const char *s2);

#endif
