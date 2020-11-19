#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <gtk/gtk.h>
#include <sys/ioctl.h>
#include <stdio.h>

//Window size
//===================================
#define WIN_WIDTH_MIN 715
#define WIN_HEIGHT_MIN 480
#define CUR_WIDTH 715
#define CUR_HEIGHT 480
//===================================

//Colors
//===================================
//Standard ones
#define MX_1F1F1F 0.12
#define MX_E1E1E1 0.89
//Colorful theme
//===================================

GdkPixbuf *mx_create_pixbuf(const gchar *filename);
void mx_tooltip(char *str, void *data);

gboolean mx_on_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif
