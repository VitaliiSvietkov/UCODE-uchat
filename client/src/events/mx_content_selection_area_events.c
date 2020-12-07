#include "../../inc/uchat_client.h"

// Messages button
//==================================================================================
void messages_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void messages_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void messages_click(GtkWidget *widget, GdkEventButton *event) {
    if (messages_image.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (t_active_image != NULL) {
            gtk_widget_unset_state_flags(GTK_WIDGET(t_active_image->box), GTK_STATE_FLAG_CHECKED);        
            t_active_image->active = false;
        }
        t_active_image = &messages_image;
        t_active_image->active = true;
        gtk_widget_show_all(GTK_WIDGET(chat_enter_area));
        gtk_widget_hide(GTK_WIDGET(tick_image.box));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = chats_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
}
//==================================================================================

// Contacts button
//==================================================================================
void contacts_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void contacts_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void contacts_click(GtkWidget *widget, GdkEventButton *event) {
    if (contacts_image.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (t_active_image != NULL) {
            gtk_widget_unset_state_flags(GTK_WIDGET(t_active_image->box), GTK_STATE_FLAG_CHECKED);        
            t_active_image->active = false;
        }
        t_active_image = &contacts_image;
        t_active_image->active = true;
        gtk_widget_hide(GTK_WIDGET(chat_enter_area));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = contacts_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
}
//==================================================================================

// Settings button
//==================================================================================
void settings_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void settings_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void settings_click(GtkWidget *widget, GdkEventButton *event) {
    if (settings_image.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (t_active_image != NULL) {
            gtk_widget_unset_state_flags(GTK_WIDGET(t_active_image->box), GTK_STATE_FLAG_CHECKED);
            t_active_image->active = false;
        }
        t_active_image = &settings_image;
        t_active_image->active = true;
        gtk_widget_hide(GTK_WIDGET(chat_enter_area));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = settings_menu;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
}
//==================================================================================
