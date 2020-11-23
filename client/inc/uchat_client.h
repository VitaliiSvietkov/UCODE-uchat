#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <gtk/gtk.h>
#include <sys/ioctl.h>
#include <stdio.h>

// Window size
//===================================
#define WIN_WIDTH_MIN 715
#define WIN_HEIGHT_MIN 480
#define CUR_WIDTH 715
#define CUR_HEIGHT 480
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
void mx_free_images(void); // Look "mx_load_images.c"
//===================================

void mx_init_window(GtkWidget *window, GdkPixbuf *icon);
void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
void mx_tooltip(char *str, void *data);

gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_settings(GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif
