#include "../../inc/uchat_client.h"

// Edit_user icon
//=================================================================================
void edit_user_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_user_image.box), 
        GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void edit_user_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_user_image.box), GTK_STATE_FLAG_PRELIGHT);
}

void edit_user_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        mx_create_edit_user_form();
        gtk_widget_show_all(GTK_WIDGET(blackout));
        gtk_widget_hide(GTK_WIDGET(edit_username_event_screen));
        gtk_widget_hide(GTK_WIDGET(edit_pseudonim_event_screen));
    }
}
//=================================================================================

// Change_account icon
//=================================================================================
void change_account_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(change_account_image.box), 
        GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void change_account_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(change_account_image.box), 
        GTK_STATE_FLAG_PRELIGHT);
}

void change_account_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        mx_create_registration_menu();
        gtk_widget_show_all(GTK_WIDGET(authorization_area));
        gtk_widget_hide(GTK_WIDGET(chat_area));
        gtk_widget_hide(GTK_WIDGET(registration_menu_1));
        gtk_widget_hide(GTK_WIDGET(registration_menu_2));
    }
}
//=================================================================================

// Chat_settings icon
//=================================================================================
void chat_settings_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(chat_settings_image.box), 
        GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void chat_settings_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(chat_settings_image.box), 
        GTK_STATE_FLAG_PRELIGHT);
}
//=================================================================================

// Language icon
//=================================================================================
void language_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(language_image.box), 
        GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void language_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(language_image.box), 
        GTK_STATE_FLAG_PRELIGHT);
}

void language_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        mx_create_language_menu();
    }
}
//=================================================================================
