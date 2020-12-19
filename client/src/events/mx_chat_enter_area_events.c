#include "../../inc/uchat_client.h"

// Add button
//========================================================

//========================================================

// Message entry field
//=================================================================================
void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event) {
    int len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    if (len > 0) {
        gtk_widget_hide(GTK_WIDGET(ban_image.box));
        gtk_widget_show(GTK_WIDGET(tick_image.box));
    }
    else {
        gtk_widget_hide(GTK_WIDGET(tick_image.box));
        gtk_widget_show(GTK_WIDGET(ban_image.box));
    }
}
//=================================================================================

// Tick button
//=========================================================
void mx_send_message(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_message *msg = (t_message *)malloc(sizeof(t_message));
        msg->text = strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
        msg->image = NULL;
        msg->usr_id = t_user.id;
        mx_add_message(messages_box, msg);
        free(msg->text);
        free(msg);
    }
}
//========================================================

// More button
//=========================================================

//=========================================================
