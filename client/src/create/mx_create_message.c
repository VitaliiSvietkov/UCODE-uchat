#include "../../inc/uchat_client.h"

GtkWidget *mx_create_message(t_message *data) {
    GtkWidget *eventbox = gtk_event_box_new();
    if (data->uid == t_user.id)
        gtk_widget_set_name(GTK_WIDGET(eventbox), "usr_message");
    else
        gtk_widget_set_name(GTK_WIDGET(eventbox), "message");
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    if (data->image != NULL) {
        GtkWidget *image = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(image), gdk_pixbuf_get_width(GDK_PIXBUF(data->image)), 
            gdk_pixbuf_get_height(GDK_PIXBUF(data->image)));
        g_signal_connect(G_OBJECT(image), "draw", G_CALLBACK(draw_image), data->image);
        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
    }
    if (data->text != NULL) {
        GtkWidget *label = gtk_label_new(data->text);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
        gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_START);
        gtk_widget_set_margin_top(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_start(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_end(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_bottom(GTK_WIDGET(label), 10);
    }

    return eventbox;
}
