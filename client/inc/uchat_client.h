#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

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
typedef struct s_image_button
{
    bool active;
    char *basic;
    char *hovered;
    GtkWidget *standard;
    GtkWidget *colorful;
} t_image_button;

t_image_button settings_img;
t_image_button contacts_img;
t_image_button messages_img;

t_image_button add_img;
t_image_button ban_img;
t_image_button tick_img;
t_image_button more_img;

t_image_button edit_user_img;
t_image_button chat_settings_img;
t_image_button language_img;

t_image_button *t_active;

// EventBoxes for images
struct
{
    GtkWidget *contacts_box;
    GtkWidget *settings_box;
    GtkWidget *messages_box;
    GtkWidget *add_box;
    GtkWidget *ban_box;
    GtkWidget *tick_box;
    GtkWidget *more_box;
} t_img_event_box;

void mx_load_images(void);
//============================

GtkWidget *chats_list;
GtkWidget *contacts_list;
GtkWidget *settings_menu;
GtkWidget *active_leftbar_container;

//cairo_surface_t *avatar_image;

void mx_init_window(GtkWidget **window);

void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, GtkWidget **entry_search);
void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area);
void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area,
    GtkWidget **entry_chat);
void mx_configure_settings_menu_area(GtkWidget **settings_menu, GtkWidget **main_area);
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
void messages_enter_notify(void);
void messages_leave_notify(void);
void messages_click(GtkWidget *widget, GdkEventButton *event);

void contacts_enter_notify(void);
void contacts_leave_notify(void);
void contacts_click(GtkWidget *widget, GdkEventButton *event);

void settings_enter_notify(void);
void settings_leave_notify(void);
void settings_click(GtkWidget *widget, GdkEventButton *event);

void add_enter_notify(void);
void add_leave_notify(void);

void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event);

void tick_enter_notify(void);
void tick_leave_notify(void);

void more_enter_notify(void);
void more_leave_notify(void);

void edit_user_enter_notify(GtkWidget *widget);
void edit_user_leave_notify(GtkWidget *widget);

void chat_settings_enter_notify(GtkWidget *widget);
void chat_settings_leave_notify(GtkWidget *widget);

void language_enter_notify(GtkWidget *widget);
void language_leave_notify(GtkWidget *widget);
//================================

#endif
