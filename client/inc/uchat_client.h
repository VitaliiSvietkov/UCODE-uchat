#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <gtk/gtk.h>
#include <sys/ioctl.h>
#include <stdio.h>

// Window size
//===================================
#define WIN_WIDTH_MIN 915
#define WIN_HEIGHT_MIN 680
gint CUR_WIDTH;
gint CUR_HEIGHT;
//===================================

// Colors
//===================================
// Standard ones
#define MX_1F1F1F 0.12
#define MX_E1E1E1 0.89
// Colorful theme

//===================================

// Images
//===================================
struct
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_settings;

struct
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_contacts;

struct
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_messages;

// EventBoxes for images
struct
{
    GtkWidget *contacts_box;
    GtkWidget *settings_box;
    GtkWidget *messages_box;
} t_img_event_box;

void mx_load_images(void);
//===================================

void mx_init_window(GtkWidget **window, GdkPixbuf **icon);

void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, GtkWidget **entry_search);
void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area);
void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area,
    GtkWidget **entry_chat);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
void mx_tooltip(char *str, void *data);

// All draw functions are in "mx_draw_functions.c"
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);

// Event callback functions
void messages_enter_notify(GtkWidget *widget, gpointer data);
void messages_leave_notify(GtkWidget *widget, gpointer data);
void contacts_enter_notify(GtkWidget *widget, gpointer data);
void contacts_leave_notify(GtkWidget *widget, gpointer data);
void settings_enter_notify(GtkWidget *widget, gpointer data);
void settings_leave_notify(GtkWidget *widget, gpointer data);

#endif
