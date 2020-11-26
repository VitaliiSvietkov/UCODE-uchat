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

void settings_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_settings.standard), "client/img/settings-standard-hovered.png");
}

void settings_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_settings.standard), "client/img/settings-standard.png");
}

void messages_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_messages.standard), "client/img/messages-standard-hovered.png");
}

void messages_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    gtk_image_set_from_file(GTK_IMAGE(t_messages.standard), "client/img/messages-standard.png");
}
