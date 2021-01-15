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
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 5 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 5) {
        gtk_widget_set_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT, TRUE);
    }
}

void login_btn_leave_notify(void) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 5 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 5) {
        gtk_widget_unset_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT);
    }
}

void authorization(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(password))) > 5 && strlen(gtk_entry_get_text(GTK_ENTRY(login))) > 5) {
        if (t_user.id == -1) {
            GtkWidget *background = gtk_drawing_area_new();
            gtk_fixed_put(GTK_FIXED(chat_area), background, 0, 0);
            gtk_widget_set_size_request(GTK_WIDGET(background), CUR_WIDTH, CUR_HEIGHT);
            g_signal_connect(G_OBJECT(background), "draw",
                            G_CALLBACK(mx_draw_event_background), NULL);

            GtkWidget *label = gtk_label_new("");
            gtk_widget_set_name(GTK_WIDGET(label), "DefaultLabel");
            gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
            gtk_fixed_put(GTK_FIXED(chat_area), label, CUR_WIDTH - CUR_WIDTH / 2.5 - 50, CUR_HEIGHT / 2 - 20);
            labels_head = mx_label_create_node(label, 4);
        }
        const char *login1 = gtk_entry_get_text(GTK_ENTRY(login));
        const char *password1 = gtk_entry_get_text(GTK_ENTRY(password));
        if(mx_write_user_data_from_bd_after_auth(login1, password1) == 1) {
            gtk_widget_show(GTK_WIDGET(data)); 
        }
        else {
            // Create a header for left area
            mx_configure_left_header();
            // Create a selection area
            mx_configure_content_selection_area();
            // Create a chat list area
            mx_configure_chats_list();

            // Create a contacts list area
            contacts_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_fixed_put(GTK_FIXED(chat_area), contacts_list, 0, 95);
            mx_configure_settings_menu_area();

            mx_update_user_data_preview();
            gtk_widget_destroy(GTK_WIDGET(authorization_container));
            gtk_widget_hide(GTK_WIDGET(authorization_area));

            gtk_widget_show_all(GTK_WIDGET(chat_area));
            gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
            gtk_widget_grab_focus(GTK_WIDGET(chat_area));
            gtk_widget_hide(GTK_WIDGET(chats_list));
            gtk_widget_hide(GTK_WIDGET(contacts_list));
        }
    }
}

void hide_authorization_click(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    gtk_widget_hide(GTK_WIDGET(log_in_menu));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
    gtk_widget_hide(GTK_WIDGET(data));
}

void hide_registration_click(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    gtk_entry_set_text(GTK_ENTRY(login_reg), "");
    gtk_entry_set_text(GTK_ENTRY(password_reg), "");
    gtk_entry_set_text(GTK_ENTRY(password_reg_confirm), "");
    gtk_entry_set_text(GTK_ENTRY(login), "");
    gtk_entry_set_text(GTK_ENTRY(password), "");
    gtk_widget_hide(GTK_WIDGET(registration_menu_1));
    gtk_widget_show_all(GTK_WIDGET(log_in_menu));
    gtk_widget_hide(GTK_WIDGET(data)); 
}

// Events which change opacity of "next" buttons
//===========================================================================
void data_change_registration_event(GtkWidget *widget, GdkEvent *event) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
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

void transition_registration_click(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg))) > 0 && strlen(gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) > 0) {
        if (mx_check_login_reg(gtk_entry_get_text(GTK_ENTRY(login_reg))) == 1) {
            gtk_label_set_text(GTK_LABEL(data), text_for_labels[33]);
            gtk_widget_show(GTK_WIDGET(data));
        }
        else {
            if (mx_strcmp(gtk_entry_get_text(GTK_ENTRY(password_reg)), gtk_entry_get_text(GTK_ENTRY(password_reg_confirm))) == 0) {
                gtk_widget_hide(GTK_WIDGET(registration_menu_1));
                gtk_widget_show_all(GTK_WIDGET(registration_menu_2));
            }
            else {
                gtk_label_set_text(GTK_LABEL(data), text_for_labels[31]);
                gtk_widget_show(GTK_WIDGET(data)); 
            }
        }
    }
}

void hide_registration_click_2(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    gtk_entry_set_text(GTK_ENTRY(firstname_reg), "");
    gtk_entry_set_text(GTK_ENTRY(secondname_reg), "");
    gtk_widget_hide(GTK_WIDGET(registration_menu_2));
    gtk_widget_show_all(GTK_WIDGET(registration_menu_1));
    gtk_widget_hide(GTK_WIDGET(data));
}

void authorization_after_registration(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    if (strlen(gtk_entry_get_text(GTK_ENTRY(firstname_reg))) > 0) {
        const char *login_var = gtk_entry_get_text(GTK_ENTRY(login_reg));
        const char *password_var = gtk_entry_get_text(GTK_ENTRY(password_reg));
        const char *name = gtk_entry_get_text(GTK_ENTRY(firstname_reg));
        const char *sname = gtk_entry_get_text(GTK_ENTRY(secondname_reg));
            mx_add_user_data(login_var, password_var, name, sname);
        gtk_entry_set_text(GTK_ENTRY(login), "");
        gtk_entry_set_text(GTK_ENTRY(password), "");
        gtk_entry_set_text(GTK_ENTRY(login_reg), "");
        gtk_entry_set_text(GTK_ENTRY(password_reg), "");
        gtk_entry_set_text(GTK_ENTRY(password_reg_confirm), "");
        gtk_entry_set_text(GTK_ENTRY(firstname_reg), "");
        gtk_entry_set_text(GTK_ENTRY(secondname_reg), "");
        gtk_widget_hide(GTK_WIDGET(registration_menu_2));
        gtk_widget_show_all(GTK_WIDGET(log_in_menu));
        gtk_widget_hide(GTK_WIDGET(data));
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
        gtk_widget_destroy(authorization_container);
        gtk_widget_hide(GTK_WIDGET(authorization_area));
        gtk_widget_show_all(GTK_WIDGET(chat_area));
        gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(chat_area));
        gtk_widget_hide(GTK_WIDGET(chats_list));
        gtk_widget_hide(GTK_WIDGET(contacts_list));
    }
}
