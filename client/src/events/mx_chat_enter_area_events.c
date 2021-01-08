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

        if (filename != NULL) {
            struct stat buf;
            stat(filename, &buf);
            if (buf.st_size < 20971520) // > 20mb
                mx_create_attach_form(entry, filename);
            else
                mx_run_error_pop_up("The file is too big!");
        }
    }
}

void mx_attach_send_message_on_enter(GtkWidget *widget, GdkPixbuf *pixbuf) {
    char *text = NULL;
    if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        text = strdup(gtk_entry_get_text(GTK_ENTRY(widget)));
    
    t_message *msg = mx_push_back_message(&curr_room_msg_head,
        text, 
        t_user.id, 
        pixbuf);
    mx_add_message(messages_box, msg);

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
        t_message *msg = mx_push_back_message(&curr_room_msg_head,
            strdup(gtk_entry_get_text(GTK_ENTRY(widget))), 
            t_user.id, 
            NULL);
        mx_add_message(messages_box, msg);
        gtk_entry_set_text(GTK_ENTRY(widget), "");
    }
}
//=================================================================================

// Tick button
//=================================================================================
void mx_send_message(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (mx_strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0) {
            t_message *msg = mx_push_back_message(&curr_room_msg_head,
                strdup(gtk_entry_get_text(GTK_ENTRY(entry))), 
                t_user.id, 
                NULL);
            mx_add_message(messages_box, msg);
            gtk_entry_set_text(GTK_ENTRY(entry), "");
        }
    }
}
//=================================================================================

// More button
//=================================================================================
void more_content_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
        if (!(flags & GTK_STATE_FLAG_CHECKED)) {

            flags = gtk_widget_get_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 1, 1)));
            if (flags & GTK_STATE_FLAG_CHECKED) {
                gtk_widget_unset_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 1, 1)), GTK_STATE_FLAG_CHECKED);
            }
            else {
                gtk_widget_unset_state_flags(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(data), 3, 1)), GTK_STATE_FLAG_CHECKED);
            }

            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, TRUE);

        }
    }
}

void mx_more_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (!(data->active)) {
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
            data->active = true;

            more_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(GTK_WIDGET(more_box), "more_box");
            GtkAllocation alloc;
            gtk_widget_get_allocation(GTK_WIDGET(widget), &alloc);
            gtk_fixed_put(GTK_FIXED(chat_area), more_box, alloc.x - 265, alloc.y - 515);

            GtkWidget *more_grid = gtk_grid_new();
            gtk_container_add(GTK_CONTAINER(more_box), more_grid);
            gtk_widget_set_valign(GTK_WIDGET(more_grid), GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(GTK_WIDGET(more_grid), 300, 480);
            gtk_widget_set_margin_top(GTK_WIDGET(more_grid), 10);
            gtk_widget_set_margin_bottom(GTK_WIDGET(more_grid), 10);

            GtkWidget *stickers_eventbox = gtk_event_box_new();
            gtk_widget_set_size_request(GTK_WIDGET(stickers_eventbox), 150, 45);
            gtk_widget_set_name(GTK_WIDGET(stickers_eventbox), "stickers_eventbox");
            gtk_widget_set_state_flags(GTK_WIDGET(stickers_eventbox), GTK_STATE_FLAG_CHECKED, TRUE);
            g_signal_connect(G_OBJECT(stickers_eventbox), "button_press_event",
                G_CALLBACK(more_content_click), more_grid);
            gtk_grid_attach(GTK_GRID(more_grid), stickers_eventbox, 1, 1, 2, 1);

            GtkWidget *gifs_eventbox = gtk_event_box_new();
            gtk_widget_set_size_request(GTK_WIDGET(gifs_eventbox), 150, 45);
            gtk_widget_set_name(GTK_WIDGET(gifs_eventbox), "gifs_eventbox");
            g_signal_connect(G_OBJECT(gifs_eventbox), "button_press_event",
                G_CALLBACK(more_content_click), more_grid);
            gtk_grid_attach(GTK_GRID(more_grid), gifs_eventbox, 3, 1, 1, 1);
            
            
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
