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
    cairo_surface_t *standard;
    cairo_surface_t *colorful;
} t_settings;

struct
{
    cairo_surface_t *standard;
    cairo_surface_t *colorful;
} t_contacts;

struct
{
    cairo_surface_t *standard;
    cairo_surface_t *colorful;
} t_messages;

struct
{
    cairo_surface_t *standard;
    cairo_surface_t *colorful;
} t_more;

void mx_load_images(void);
void mx_free_images(void); // Look in "mx_load_images.c"
//===================================

void mx_init_window(GtkWidget **window, GdkPixbuf **icon);

void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, GtkWidget **entry_search);
void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area, 
    GtkWidget **messages, GtkWidget **contacts, GtkWidget **settings);
void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
void mx_tooltip(char *str, void *data);

// All draw functions are in "mx_draw_functions.c"
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_settings(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_messages(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_contacts(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_more(GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif
