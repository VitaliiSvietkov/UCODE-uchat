#include "../../inc/uchat_client.h"

void button_shine(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0
        && strlen(gtk_entry_get_text(GTK_ENTRY(widget))) >= 5) {
        gtk_widget_set_opacity(GTK_WIDGET(login_btn), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(login_btn), 0.5);
    }
    if (strlen(gtk_entry_get_text(GTK_ENTRY(widget))) < 5) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
    else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    }
}

void activate_prelight_with_condition_entry(GtkWidget *widget, GdkEvent *event, gpointer *entry) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
    }
}

void deactivate_prelight_with_condition_entry(GtkWidget *widget, GdkEvent *event, gpointer *entry) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    }
}


void login_btn_enter_notify(void) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void login_btn_leave_notify(void) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT);
    }
}

void authorization(GtkWidget *widget) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_destroy(GTK_WIDGET(authorization_fixed_container));
        gtk_widget_hide(GTK_WIDGET(authorization_area));
        gtk_widget_show_all(GTK_WIDGET(chat_area));
    }
}

void hide_authorization_click(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
}

void hide_registration_click(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_1));
    gtk_widget_show_all(GTK_WIDGET(data));
     
}

// Events which change opacity of "next" buttons
//===========================================================================
void data_change_registration_event(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0) {
        gtk_widget_set_opacity(GTK_WIDGET(next_btn), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(next_btn), 0.5);
    }
}

void data_change_registration_event_2(GtkWidget *widget, gpointer data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0) {
        gtk_widget_set_opacity(GTK_WIDGET(data), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(data), 0.5);
    }
}
//===========================================================================

void next_btn_enter_notify(GtkWidget *widget, GdkEvent *event, gpointer *data) { 
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(data))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void next_btn_leave_notify(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(data))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    }
}

void transition_registration_click(GtkWidget *widget) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
        gtk_widget_hide(GTK_WIDGET(registration_menu_1));
        gtk_widget_show_all(GTK_WIDGET(registration_menu_2));
    }
}

void hide_registration_click_2(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_2));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
}

void authorization_after_registration(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(data))) > 0) {
        gtk_widget_hide(GTK_WIDGET(registration_menu_2));
        gtk_widget_show_all(GTK_WIDGET(log_in_menu));
    }
}

void password_entry_change(GtkWidget *widget) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(widget))) < 5) {
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
    else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    }
}

void eye_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (!gtk_entry_get_visibility(GTK_ENTRY(data))) {
            gtk_entry_set_visibility(GTK_ENTRY(data), TRUE);
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        }
        else {
            gtk_entry_set_visibility(GTK_ENTRY(data), FALSE);
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED);
        }
    }
}

void authorization_close(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(authorization_fixed_container);
        gtk_widget_hide(GTK_WIDGET(authorization_area));
        gtk_widget_show_all(GTK_WIDGET(chat_area));
        gtk_widget_hide(GTK_WIDGET(message_enter_area));
        gtk_widget_hide(GTK_WIDGET(chats_list));
        gtk_widget_hide(GTK_WIDGET(contacts_list));
    }
}
