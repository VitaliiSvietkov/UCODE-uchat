#include "../../inc/uchat_client.h"

// Change avatar button
//============================================================================================
void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event) {
    if (widget) {}
    if (event) {}
    printf("BUTTON PRESSED\n");
}
//============================================================================================

// Edit username field
//============================================================================================
void edit_username_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_username_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_username_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
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
    if (widget) {}
}



void return_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_entry_set_text(GTK_ENTRY(change_fname_entry), "");
        gtk_entry_set_text(GTK_ENTRY(change_sname_entry), "");
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
    if (widget) {}
}

void commit_username_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        if (NewFirstName == NULL)
            NewFirstName = mx_strjoin(NewFirstName, gtk_entry_get_text(GTK_ENTRY(change_fname_entry)));
        else {
            free(NewFirstName);
            NewFirstName = NULL;
            NewFirstName = mx_strjoin(NewFirstName, gtk_entry_get_text(GTK_ENTRY(change_fname_entry)));
        }
        if (NewSecondName == NULL) {
            if (strlen(gtk_entry_get_text(GTK_ENTRY(change_sname_entry))) == 0)
                NewSecondName = mx_strjoin(NewSecondName, "");
            else
                NewSecondName = mx_strjoin(NewSecondName, gtk_entry_get_text(GTK_ENTRY(change_sname_entry)));
        }
        else {
            free(NewSecondName);
            NewSecondName = NULL;
            if (strlen(gtk_entry_get_text(GTK_ENTRY(change_sname_entry))) != 0)
                NewSecondName = mx_strjoin(NewSecondName, gtk_entry_get_text(GTK_ENTRY(change_sname_entry)));
        }
        gtk_entry_set_text(GTK_ENTRY(change_fname_entry), "");
        gtk_entry_set_text(GTK_ENTRY(change_sname_entry), "");
        

        char *username_tmp = strdup(NewFirstName);
        username_tmp = mx_strjoin(username_tmp, " ");
        username_tmp = mx_strjoin(username_tmp, NewSecondName);
        gtk_label_set_text(GTK_LABEL(edit_username_label), username_tmp);
        free(username_tmp);

        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
    if (widget) {}
}

//============================================================================================

// Edit pseudonim field
//============================================================================================
void edit_pseudo_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_pseudo_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT);
}

void return_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_entry_set_text(GTK_ENTRY(change_pseudo_entry), "");
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
    if (widget) {}
}

void commit_pseudonim_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        if (NewPseudonim == NULL)
            NewPseudonim = mx_strjoin(NewPseudonim, gtk_entry_get_text(GTK_ENTRY(change_pseudo_entry)));
        else {
            free(NewPseudonim);
            NewPseudonim = NULL;
            NewPseudonim = mx_strjoin(NewPseudonim, gtk_entry_get_text(GTK_ENTRY(change_pseudo_entry)));
        }
        gtk_entry_set_text(GTK_ENTRY(change_pseudo_entry), "");

        gtk_label_set_text(GTK_LABEL(edit_pseudo_label), NewPseudonim);
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
    if (widget) {}
}
//============================================================================================

// Change description field
//============================================================================================
void change_description_entry_change_event(GtkWidget *widget) {
    if (widget) {}
    if (NewDescription != NULL) {
        free(NewDescription);
        NewDescription = NULL;
    }
    GtkTextIter *start = NULL;
    GtkTextIter *end = NULL;
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(widget), start, 1);
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(widget), end, 1);
    gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(widget), start);
    gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER(widget), end);
    NewDescription = mx_strjoin(NewDescription, gtk_text_buffer_get_text(GTK_TEXT_BUFFER(widget), start, end, FALSE));
}
//============================================================================================


void commit_edit_user_click_event(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        free(t_user.FirstName);
        t_user.FirstName = NULL;
        t_user.FirstName = mx_strjoin(t_user.FirstName, NewFirstName);
        free(NewFirstName);
        NewFirstName = NULL;

        free(t_user.SecondName);
        t_user.SecondName = NULL;
        t_user.SecondName = mx_strjoin(t_user.SecondName, NewSecondName);
        free(NewSecondName);
        NewSecondName = NULL;

        char *username_tmp = strdup(t_user.FirstName);
        username_tmp = mx_strjoin(username_tmp, " ");
        username_tmp = mx_strjoin(username_tmp, t_user.SecondName);
        gtk_label_set_text(GTK_LABEL(username), username_tmp);
        free(username_tmp);

        free(t_user.pseudonim);
        t_user.pseudonim = NULL;
        t_user.pseudonim = mx_strjoin(t_user.pseudonim, NewPseudonim);
        free(NewPseudonim);
        NewPseudonim = NULL;
        gtk_label_set_text(GTK_LABEL(contact_info), t_user.pseudonim);

        if (NewDescription != NULL) {
            free(t_user.description);
            t_user.description = NULL;
            t_user.description = mx_strjoin(t_user.description, NewDescription);
            free(NewDescription);
        }

        gtk_widget_destroy(GTK_WIDGET(back_blackout));
    }
    if (widget) {}
}
