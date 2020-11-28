#include "../inc/uchat_client.h"

// Messages button
//=============================================================
void messages_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.hovered);
}

void messages_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.basic);
}

void messages_click(GtkWidget *widget, gpointer data) {
    if (messages_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &messages_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
}
//=============================================================

// Contacts button
//=============================================================
void contacts_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!contacts_img.active)
        gtk_image_set_from_file(GTK_IMAGE(contacts_img.standard), contacts_img.hovered);
}

void contacts_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!contacts_img.active)
        gtk_image_set_from_file(GTK_IMAGE(contacts_img.standard), contacts_img.basic);
}

void contacts_click(GtkWidget *widget, gpointer data) {
    if (contacts_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &contacts_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
}
//=============================================================

// Settings button
//=============================================================
void settings_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.hovered);
}

void settings_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.basic);
}

void settings_click(GtkWidget *widget, gpointer data) {
    if (settings_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &settings_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
}
//=============================================================

// Add button
//========================================================
void add_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!add_img.active)
        gtk_image_set_from_file(GTK_IMAGE(add_img.standard), add_img.hovered);
}

void add_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!add_img.active)
        gtk_image_set_from_file(GTK_IMAGE(add_img.standard), add_img.basic);
}
//========================================================
