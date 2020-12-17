#include "../../inc/uchat_client.h"

void mx_language_eventbox_click(GtkWidget *widget, GdkEventButton *event, char *name) {
    if (!mx_strcmp(name, "English"))
        language = 0;
    else if (!mx_strcmp(name, "Русский"))
        language = 1;
    else
        language = 2;
    mx_edit_language(language);
    mx_get_language_arr();
    t_labels *temp = labels_head->next;
    while (temp != NULL) {
        gtk_label_set_text(GTK_LABEL(temp->data), text_for_labels[temp->index]);
        temp = temp->next;
    }
    gtk_widget_destroy(GTK_WIDGET(blackout));
}

void mx_language_close(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(blackout));
    }
}
