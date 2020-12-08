#include "../../inc/uchat_client.h"

void data_change_event(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_set_opacity(GTK_WIDGET(login_btn), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(login_btn), 0.5);
    }

    if (event) {}
    if (widget) {}
}

void login_btn_enter_notify_event() {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void login_btn_leave_notify_event() {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT);
    }
}


void registration_label_enter_notify_event(GtkWidget *widget, GdkEvent *event, GtkWidget *data) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    if (data) {}
    if (event) {}
}

void registration_label_leave_notify_event(GtkWidget *widget, GdkEvent *event, GtkWidget *data) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
        if (data) {}
    if (event) {}
}

void hide_autorization_click(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(log_in_menu));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
    if(widget) {}
}

void back_btn_enter_notify_event() { 
    gtk_widget_set_state_flags(GTK_WIDGET(back_btn), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void back_btn_leave_notify_event() {
    gtk_widget_unset_state_flags(GTK_WIDGET(back_btn), GTK_STATE_FLAG_PRELIGHT);
}

void hide_registration_click(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_1));
    gtk_widget_show_all(GTK_WIDGET(log_in_menu));
    if(widget) {}
}

void data_change_registration_event(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
        gtk_widget_set_opacity(GTK_WIDGET(next_btn), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(next_btn), 0.5);
    }

    if (event) {}
    if (widget) {}
}

void next_btn_enter_notify_event() { 
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(next_btn), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void next_btn_leave_notify_event() {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(next_btn), GTK_STATE_FLAG_PRELIGHT);
    }
}

void transition_registration_click(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_1));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_2));
    if(widget) {}
}

void back_btn_enter_notify_event_2() { 
    gtk_widget_set_state_flags(GTK_WIDGET(back_btn_2), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void back_btn_leave_notify_event_2() {
    gtk_widget_unset_state_flags(GTK_WIDGET(back_btn_2), GTK_STATE_FLAG_PRELIGHT);
}

void next_btn_enter_notify_event_2() { 
    if (strlen(gtk_entry_get_text(GTK_ENTRY(firstname_reg))) > 0) {
        gtk_widget_set_state_flags(GTK_WIDGET(next_btn_2), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void next_btn_leave_notify_event_2() {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(firstname_reg))) > 0) {
        gtk_widget_unset_state_flags(GTK_WIDGET(next_btn_2), GTK_STATE_FLAG_PRELIGHT);
    }
}

void hide_registration_click_2(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_2));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
    if(widget) {}
}

void data_change_registration_event_2(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(firstname_reg))) > 0) {
        gtk_widget_set_opacity(GTK_WIDGET(next_btn_2), 1.0);
    }
    else {
         gtk_widget_set_opacity(GTK_WIDGET(next_btn_2), 0.5);
    }

    if (event) {}
    if (widget) {}
}

void autorization_after_registration(GtkWidget *widget) {
    gtk_widget_hide(GTK_WIDGET(registration_menu_2));
    gtk_widget_show_all(GTK_WIDGET(log_in_menu));
    if(widget) {}
}

void autorization(GtkWidget *widget) {
    gtk_widget_show_all(GTK_WIDGET(chat_area));
    gtk_widget_hide(GTK_WIDGET(back_black));
    if(widget) {}
}
