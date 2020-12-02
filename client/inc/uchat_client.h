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
//=====================
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
//=====================

GtkWidget *main_area;

GtkWidget *chats_list;
GtkWidget *contacts_list;
GtkWidget *settings_menu;
GtkWidget *active_leftbar_container;

GtkWidget *back_blackout;
GtkWidget *edit_user_form;

//cairo_surface_t *avatar_image;

void mx_init_window(GtkWidget **window);

void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, GtkWidget **entry_search);
void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area);
void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area,
    GtkWidget **entry_chat);
void mx_configure_settings_menu_area(GtkWidget **settings_menu, GtkWidget **main_area);
void mx_create_edit_user_form(void);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
GdkPixbuf *mx_get_pixbuf_with_size(char *path, int w, int h);
void mx_tooltip(char *str, void *data);

// All draw functions are in "mx_draw_functions.c"
//==========================================================================================
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_delimiter(GtkWidget *widget, cairo_t *cr);
gboolean mx_draw_event_avatar(GtkWidget *widget, cairo_t *cr);
//==========================================================================================

// Event callback functions (look in "mx_events.c")
//================================
void image_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data);
void image_enter_notify(GtkWidget *widget);
void image_leave_notify(GtkWidget *widget);

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

void close_image_enter_notify_event(GtkWidget *widget);
void close_image_leave_notify_event(GtkWidget *widget);
void close_image_click_event(GtkWidget *widget, GdkEventButton *event);
//================================

#endif
