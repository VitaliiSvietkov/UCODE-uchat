#include "../inc/uchat_client.h"

GtkWidget *mx_language_create_box(char *path, char *name) {
    GtkWidget *eventbox = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(eventbox), 400, 60);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(eventbox), box);
    GdkPixbuf *pixbuf = mx_get_pixbuf_with_size(path, 50, 50);
    GtkWidget *flag = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
    g_object_unref(G_OBJECT(pixbuf));
    gtk_box_pack_start(GTK_BOX(box), flag, FALSE, FALSE, 0);
    GtkWidget *label = gtk_label_new(name);
    gtk_widget_set_name(GTK_WIDGET(label), "language_label");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, FALSE, 0);

    if (!mx_strcmp(name, "English") && language == 0)
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/radiobox_checked.png", 20, 20);
    else if (!mx_strcmp(name, "Русский") && language == 1)
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/radiobox_checked.png", 20, 20);
    else if (!mx_strcmp(name, "Українська") && language == 2)
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/radiobox_checked.png", 20, 20);
    else
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/radiobox.png", 20, 20);

    GtkWidget *radiobox = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
    g_object_unref(G_OBJECT(pixbuf));
    gtk_box_pack_start(GTK_BOX(box), radiobox, FALSE, FALSE, 20);
    gtk_widget_set_halign(GTK_WIDGET(radiobox), GTK_ALIGN_END);

    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(mx_language_eventbox_click), name);

    return eventbox;
}
