#include "../inc/uchat_client.h"

void mx_add_message(GtkWidget *container, t_message *message) {
    GtkWidget *msg = mx_create_message(message);
    if (message->usr_id == t_user.id) {
        gtk_widget_set_halign(GTK_WIDGET(msg), GTK_ALIGN_END);
        gtk_widget_set_margin_end(GTK_WIDGET(msg), 5);
    }
    else
        gtk_widget_set_halign(GTK_WIDGET(msg), GTK_ALIGN_START);

    gtk_widget_set_margin_top(GTK_WIDGET(msg), 5);
    gtk_widget_set_margin_bottom(GTK_WIDGET(msg), 5);

    gtk_box_pack_start(GTK_BOX(container), msg, FALSE, FALSE, 0); 
    gtk_widget_show_all(GTK_WIDGET(msg));
}
