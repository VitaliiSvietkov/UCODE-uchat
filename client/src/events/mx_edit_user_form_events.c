#include "../../inc/uchat_client.h"

// Change avatar button
//============================================================================================
void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event) {
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
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        g_object_unref(G_OBJECT(NewAvatar));
        NewAvatar = mx_get_pixbuf_with_size(filename, 100, 100);
        free(filename);
        gtk_widget_queue_draw(GTK_WIDGET(edit_user_main_screen));
    }

    gtk_widget_destroy (dialog);
}
//============================================================================================

// Edit username field
//============================================================================================
void edit_username_eventbox_enter_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_username_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_username_eventbox_leave_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_username_icon), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT);
}

void edit_eventbox_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(edit_user_main_screen));
        gtk_widget_show_all(GTK_WIDGET(data));
    }
}

void fname_entry_changed_event(GtkWidget *widget) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(widget))) == 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
    else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    }
}



void return_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_entry_set_text(GTK_ENTRY(change_fname_entry), NewFirstName);
        gtk_entry_set_text(GTK_ENTRY(change_sname_entry), NewSecondName);
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
}

void commit_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1
        && strlen(gtk_entry_get_text(GTK_ENTRY(change_fname_entry))) != 0) {
        gtk_widget_hide(GTK_WIDGET(data));

        free(NewFirstName);
        NewFirstName = NULL;
        NewFirstName = mx_strjoin(NewFirstName, gtk_entry_get_text(GTK_ENTRY(change_fname_entry)));

        if (NewSecondName != NULL) {
            free(NewSecondName);
            NewSecondName = strdup("");
        }
        if (strlen(gtk_entry_get_text(GTK_ENTRY(change_sname_entry))) != 0)
            NewSecondName = mx_strjoin(NewSecondName, gtk_entry_get_text(GTK_ENTRY(change_sname_entry)));

        gtk_entry_set_text(GTK_ENTRY(change_fname_entry), NewFirstName);
        gtk_entry_set_text(GTK_ENTRY(change_sname_entry), NewSecondName);
        

        char *username_tmp = strdup(NewFirstName);
        username_tmp = mx_strjoin(username_tmp, " ");
        username_tmp = mx_strjoin(username_tmp, NewSecondName);
        gtk_label_set_text(GTK_LABEL(edit_username_label), username_tmp);
        free(username_tmp);

        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
}

//============================================================================================

// Edit pseudonim field
//============================================================================================
void edit_pseudo_eventbox_enter_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_pseudo_eventbox_leave_notify(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT);
}

void pseudo_entry_changed_event(GtkWidget *widget) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(widget))) < 5) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
    else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    }
}

void return_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_entry_set_text(GTK_ENTRY(change_pseudo_entry), NewPseudonim);
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
}

void commit_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1 
        && strlen(gtk_entry_get_text(GTK_ENTRY(change_pseudo_entry))) >= 5) {
        gtk_widget_hide(GTK_WIDGET(data));
        if (NewPseudonim == NULL)
            NewPseudonim = mx_strjoin(NewPseudonim, gtk_entry_get_text(GTK_ENTRY(change_pseudo_entry)));
        else {
            free(NewPseudonim);
            NewPseudonim = NULL;
            NewPseudonim = mx_strjoin(NewPseudonim, gtk_entry_get_text(GTK_ENTRY(change_pseudo_entry)));
        }
        gtk_entry_set_text(GTK_ENTRY(change_pseudo_entry), NewPseudonim);

        gtk_label_set_text(GTK_LABEL(edit_pseudo_label), NewPseudonim);
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
}
//============================================================================================

// Change description field
//============================================================================================
void change_description_entry_change_event(GtkWidget *widget) {
    if (NewDescription != NULL) {
        free(NewDescription);
        NewDescription = NULL;
    }
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(widget), &start);
    gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER(widget), &end);
    NewDescription = mx_strjoin(NewDescription, gtk_text_buffer_get_text(GTK_TEXT_BUFFER(widget), &start, &end, FALSE));
}
//============================================================================================





// "Apply button" in the form
//============================================================================================
void commit_edit_user_click_event(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        mx_change_user_name(NewFirstName, NewSecondName);
        free(NewFirstName);
        NewFirstName = NULL;
        if (NewSecondName != NULL) {
            free(NewSecondName);
            NewSecondName = NULL;
        }

        char *username_tmp = strdup(t_user.FirstName);
        username_tmp = mx_strjoin(username_tmp, " ");
        username_tmp = mx_strjoin(username_tmp, t_user.SecondName);
        gtk_label_set_text(GTK_LABEL(username), username_tmp);
        free(username_tmp);


        mx_change_user_pseudonim(NewPseudonim);
        free(NewPseudonim);
        NewPseudonim = NULL;

        char *tmp_text = "@";
        tmp_text = mx_strjoin(tmp_text, t_user.pseudonim);
        gtk_label_set_text(GTK_LABEL(user_pseudonim), tmp_text);
        free(tmp_text);

        mx_change_user_description(NewDescription);
        free(NewDescription);
        NewDescription = NULL;
        mx_edit_name(t_user.FirstName, t_user.SecondName, t_user.pseudonim, t_user.description);

        g_object_unref(G_OBJECT(t_user.avatar));
        t_user.avatar = gdk_pixbuf_copy(GDK_PIXBUF(NewAvatar));
        g_object_unref(G_OBJECT(NewAvatar));
        gtk_widget_queue_draw(GTK_WIDGET(settings_menu));

        gtk_widget_destroy(GTK_WIDGET(blackout));
    }
}
//============================================================================================
