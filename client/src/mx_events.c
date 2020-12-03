#include "../inc/uchat_client.h"

void image_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (!(data->active)) {
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
            data->active = true;
        }
        else {
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED);
            data->active = false;
        }
    }
}
void image_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}
void image_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

// Messages button
//=============================================================
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

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = chats_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
    if (widget) {}
}
//=============================================================

// Contacts button
//=============================================================
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
        
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = contacts_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
    if (widget) {}
}
//=============================================================

// Settings button
//=============================================================
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

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
        if (active_leftbar_container != NULL)
            gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = settings_menu;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
    if (widget) {}
}
//=============================================================

// Add button
//========================================================
void add_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void add_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}
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
    if (event) {}
}
//=================================================================================

// Tick button
//=========================================================

//========================================================

// More button
//=========================================================
void more_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void more_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}
//=========================================================

// Edit_user icon in settings menu
//==================================
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
        gtk_widget_show_all(GTK_WIDGET(back_blackout));
    }
    if (widget) {}
}
//==================================

// Change_account icon in settings menu
//==================================
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
//==================================

// Chat_settings icon in settings menu
//======================================
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
//==================================

// Language icon in settings menu
//================================
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
//=================================

// Blackout
//==============================================================
void blackout_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1
        && ((event->x < CUR_WIDTH / 3 - 10 || event->x > CUR_WIDTH / 3 - 10 + 400)
            || (event->y < CUR_HEIGHT / 5 || event->y > CUR_HEIGHT / 5 + 400))) {
        gtk_widget_destroy(GTK_WIDGET(back_blackout));
    }
    if (widget) {}
}
//==============================================================

// Close image
//========================================================
void close_image_enter_notify_event(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void close_image_leave_notify_event(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void close_image_click_event(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(back_blackout));
    }
    if (widget) {}
}
//========================================================

// Change avatar button
//========================================================
void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event) {
    if (widget) {}
    if (event) {}
    printf("BUTTON PRESSED\n");
}
//========================================================

// Edit username field
//========================================================
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
//========================================================

// Edit pseudonim field
//========================================================
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
//========================================================
