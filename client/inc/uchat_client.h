#ifndef UCHAT_CLIENT
#define UCHAT_CLIENT

#include <gtk/gtk.h>

#define WIN_WIDTH_MIN 715
#define WIN_HEIGHT_MIN 480

GdkPixbuf *create_pixbuf(const gchar *filename);
void tooltip(char *str, void *data);

#endif
