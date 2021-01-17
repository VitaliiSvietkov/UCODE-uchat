#include "../../inc/uchat_client.h"

// Messages button
//==================================================================================
void messages_click(GtkWidget *widget, GdkEventButton *event) {
    mx_destroy_popups();
    if (messages_image.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (t_active_image != NULL) {
            gtk_widget_unset_state_flags(GTK_WIDGET(t_active_image->box), GTK_STATE_FLAG_CHECKED);        
            t_active_image->active = false;
        }
        t_active_image = &messages_image;
        t_active_image->active = true;

        labels_head->index = 4;
        gtk_label_set_text(GTK_LABEL(labels_head->data), text_for_labels[labels_head->index]);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = chats_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
}
//==================================================================================

// Settings button
//==================================================================================
void settings_click(GtkWidget *widget, GdkEventButton *event) {
    mx_destroy_popups();
    if (settings_image.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (t_active_image != NULL) {
            gtk_widget_unset_state_flags(GTK_WIDGET(t_active_image->box), GTK_STATE_FLAG_CHECKED);
            t_active_image->active = false;
        }
        t_active_image = &settings_image;
        t_active_image->active = true;

        gtk_label_set_text(GTK_LABEL(labels_head->data), NULL);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = settings_menu;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
}
//==================================================================================
