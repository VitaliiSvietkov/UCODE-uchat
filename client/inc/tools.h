#ifndef TOOLS
#define TOOLS
#include <gtk/gtk.h>

typedef struct s_labels
{
    int index;
    GtkWidget *data;
    struct s_labels *next;
} t_labels;
t_labels *labels_head;

t_labels *mx_label_create_node(void *data, int index);
void mx_label_pop_front(t_labels **head);
void mx_label_push_back(t_labels **list, void *data, int index);

void mx_get_language_arr(void);
GdkPixbuf *mx_create_pixbuf(const gchar *filename);
GdkPixbuf *mx_get_pixbuf_with_size(char *path, int w, int h);

#endif
