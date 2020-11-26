#include "../inc/uchat_client.h"

void contacts_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_contacts.standard), "client/img/contacts-standard-hovered.png");
}

void contacts_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_contacts.standard), "client/img/contacts-standard.png");
}

void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area) {

    *content_selection_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 48);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 8);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), CUR_WIDTH / 3 + 50, 24);

    GtkWidget *box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(box), t_contacts.standard);

    gtk_box_pack_start(GTK_BOX(*content_selection_area), t_messages.standard, TRUE, FALSE, 22);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), box, TRUE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), t_settings.standard, TRUE, FALSE, 30);

    g_signal_connect(G_OBJECT(box), "enter-notify-event", G_CALLBACK(contacts_enter_notify), NULL);
    g_signal_connect(G_OBJECT(box), "leave-notify-event", G_CALLBACK(contacts_leave_notify), NULL);
}
