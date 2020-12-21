#include "../../inc/uchat_client.h"

// Add button
//=================================================================================
void mx_attach(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        dialog = gtk_file_chooser_dialog_new ("Open File",
                                            GTK_WINDOW(window),
                                            action,
                                            "_Cancel",
                                            GTK_RESPONSE_CANCEL,
                                            "_Open",
                                            GTK_RESPONSE_ACCEPT,
                                            NULL);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        char *filename = NULL;
        if (res == GTK_RESPONSE_ACCEPT)
        {
            GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
            filename = gtk_file_chooser_get_filename (chooser);
        }
        gtk_widget_destroy (dialog);

        if (filename != NULL)
            mx_create_attach_form(entry, filename);
    }
}

void mx_attach_send_message_on_enter(GtkWidget *widget, char *filename) {
    t_message *msg = (t_message *)malloc(sizeof(t_message));
    if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        msg->text = strdup(gtk_entry_get_text(GTK_ENTRY(widget)));
    else
        msg->text = NULL;
    msg->usr_id = t_user.id;
    msg->image = mx_get_pixbuf_with_size(filename, 300, 300); 
    mx_add_message(messages_box, msg);

    if (msg->text != NULL)
        free(msg->text);
    g_object_unref(G_OBJECT(msg->image));
    free(msg);
    
    gtk_widget_destroy(GTK_WIDGET(blackout));
    blackout = NULL;

    gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(chat_area));
}
//=================================================================================

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

void mx_send_message_on_enter(GtkWidget *widget) {
    if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0) {
        t_message *msg = (t_message *)malloc(sizeof(t_message));
        msg->text = strdup(gtk_entry_get_text(GTK_ENTRY(widget)));
        msg->image = NULL;
        msg->usr_id = t_user.id;
        mx_add_message(messages_box, msg);
        free(msg->text);
        free(msg);
        gtk_entry_set_text(GTK_ENTRY(widget), "");
    }
}
//=================================================================================

// Tick button
//=================================================================================
void mx_send_message(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0) {
            t_message *msg = (t_message *)malloc(sizeof(t_message));
            msg->text = strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
            msg->image = NULL;
            msg->usr_id = t_user.id;
            mx_add_message(messages_box, msg);
            free(msg->text);
            free(msg);
            gtk_entry_set_text(GTK_ENTRY(entry), "");
        }
    }
}
//=================================================================================

// More button
//=================================================================================
void mx_more_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (!(data->active)) {
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
            data->active = true;

            more_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(more_box), "more_box");
            GtkAllocation alloc;
            gtk_widget_get_allocation(GTK_WIDGET(widget), &alloc);
            gtk_fixed_put(GTK_FIXED(chat_area), more_box, alloc.x - 260, alloc.y - 515);

            
            gtk_widget_set_size_request(GTK_WIDGET(more_box), 300, 500);

            gtk_widget_show_all(GTK_WIDGET(more_box));
        }
        else {
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED);
            data->active = false;

            gtk_widget_destroy(GTK_WIDGET(more_box));
            more_box = NULL;
        }
    }
}
//=================================================================================
