#include "../../inc/uchat_client.h"

void login_activate(GtkWidget *widget) {
    gtk_widget_set_can_focus(GTK_WIDGET(password), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(password));
}

void mx_create_registration_menu(void) {
    GtkWidget *fail_inscription = gtk_label_new(text_for_labels[31]);
    fail_auto_inscription = gtk_label_new(text_for_labels[32]);

    // Background
    //=================================================================================
    authorization_container = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(authorization_container), "authorization_container");
    gtk_fixed_put(GTK_FIXED(authorization_area), authorization_container, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(authorization_container), CUR_WIDTH, CUR_HEIGHT);
    //=================================================================================


    // Authorization menu
    //=================================================================================
    GtkWidget *main_authorization_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(main_authorization_menu), 400, 400);
    gtk_widget_set_name(GTK_WIDGET(main_authorization_menu), "registration_menu_form");
    gtk_widget_set_valign(GTK_WIDGET(main_authorization_menu), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(main_authorization_menu), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(authorization_container), main_authorization_menu);
    //=================================================================================

    // Close button
    //=================================================================================
    if(t_user.id != -1) {
        GtkWidget *close_image_box = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
        gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
        gtk_box_pack_start(GTK_BOX(main_authorization_menu), close_image_box, FALSE, FALSE, 0);
        gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

        g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
            G_CALLBACK(activate_prelight), NULL);
        g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
            G_CALLBACK(deactivate_prelight), NULL);
        g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
            G_CALLBACK(authorization_close), NULL);
    }
    //=================================================================================

    // Log in menu
    //=================================================================================
    log_in_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), log_in_menu, FALSE, FALSE, 0);

    // Inscription Log in
    GtkWidget *log_in_inscription = gtk_label_new(text_for_labels[16]);
    gtk_box_pack_start(GTK_BOX(log_in_menu), log_in_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(log_in_inscription), "authorization");

    // Entry for login
    login = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login), text_for_labels[17]);
    gtk_box_pack_start(GTK_BOX(log_in_menu), login, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(login), "changed",
        G_CALLBACK(button_shine), NULL);
    g_signal_connect(G_OBJECT(login), "activate",
        G_CALLBACK(login_activate), NULL);

    // Entry for password
    GtkWidget *password_eye_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(password_eye_box), "password_eye_back");
    gtk_widget_set_margin_start(GTK_WIDGET(password_eye_box), 20);
    gtk_widget_set_margin_end(GTK_WIDGET(password_eye_box), 20);
    gtk_box_pack_start(GTK_BOX(log_in_menu), password_eye_box, FALSE, FALSE, 30);

    password = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password), "authorization_pass_entry");
    gtk_widget_set_size_request(GTK_WIDGET(password), 335, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password), text_for_labels[18]);
    gtk_box_pack_start(GTK_BOX(password_eye_box), password, FALSE, FALSE, 0);
    gtk_entry_set_visibility(GTK_ENTRY(password), FALSE);
    g_signal_connect(G_OBJECT(password), "changed",
        G_CALLBACK(button_shine), NULL);
    g_signal_connect(G_OBJECT(password), "activate",
        G_CALLBACK(authorization), NULL);

    GtkWidget *eye_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eye_eventbox), "eye_password");
    gtk_box_pack_start(GTK_BOX(password_eye_box), eye_eventbox, FALSE, FALSE, 5);
    gtk_widget_set_size_request(GTK_WIDGET(eye_eventbox), 35, 30);
    gtk_widget_set_valign(GTK_WIDGET(eye_eventbox), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(eye_eventbox), "button_press_event",
        G_CALLBACK(eye_pressed), password);

    // Inscription fail
    gtk_box_pack_start(GTK_BOX(log_in_menu), fail_auto_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(fail_auto_inscription), "error");
    
    // Log in button
    login_btn = gtk_event_box_new();
    GtkWidget *login_btn_label = gtk_label_new(text_for_labels[19]);
    gtk_container_add(GTK_CONTAINER(login_btn), login_btn_label);
    gtk_box_pack_start(GTK_BOX(log_in_menu), login_btn, FALSE, FALSE, 10);
    gtk_widget_set_margin_top(GTK_WIDGET(login_btn), 30);
    gtk_widget_set_name(GTK_WIDGET(login_btn), "login_button");
    gtk_widget_set_opacity(GTK_WIDGET(login_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(login_btn), 200, 50);
    gtk_widget_set_halign(GTK_WIDGET(login_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(login_btn), "enter-notify-event",
        G_CALLBACK(login_btn_enter_notify), NULL);
    g_signal_connect(G_OBJECT(login_btn), "leave-notify-event",
        G_CALLBACK(login_btn_leave_notify), NULL);
    g_signal_connect(G_OBJECT(login_btn), "button_press_event",
        G_CALLBACK(authorization), fail_auto_inscription);

    // Link to registration
    GtkWidget *registration_link = gtk_event_box_new();
    GtkWidget *registration_label = gtk_label_new(text_for_labels[20]);
    gtk_widget_set_name(GTK_WIDGET(registration_label), "Registration_label");
    gtk_label_set_max_width_chars(GTK_LABEL(registration_label), 32);
    gtk_widget_set_margin_start(GTK_WIDGET(registration_link), 100);
    gtk_widget_set_margin_end(GTK_WIDGET(registration_link), 100);
    gtk_container_add(GTK_CONTAINER(registration_link), registration_label);
    gtk_box_pack_start(GTK_BOX(log_in_menu), registration_link, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_link), "Registration");
    g_signal_connect(G_OBJECT(registration_link), "enter-notify-event",
        G_CALLBACK(activate_prelight), registration_label);
    g_signal_connect(G_OBJECT(registration_link), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), registration_label);
    g_signal_connect(G_OBJECT(registration_link), "button_press_event",
        G_CALLBACK(hide_authorization_click), fail_inscription); ///////////

 
    //=================================================================================

    // Registration menu page 1
    //=================================================================================
    registration_menu_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), registration_menu_1, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(registration_menu_1), 400, 400);

    // Inscription Registration
    GtkWidget *registration_inscription = gtk_label_new(text_for_labels[21]);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription), "authorization");
    
    // Entry for a login during registration
    login_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_reg), text_for_labels[22]);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), login_reg, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(login_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    // Entry for a password during registration
    GtkWidget *password_reg_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(password_reg_box), "password_eye_back");
    gtk_widget_set_margin_start(GTK_WIDGET(password_reg_box), 20);
    gtk_widget_set_margin_end(GTK_WIDGET(password_reg_box), 20);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg_box, FALSE, FALSE, 30);
    
    password_reg = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg), "password_reg");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg), 335, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg), text_for_labels[23]);
    gtk_box_pack_start(GTK_BOX(password_reg_box), password_reg, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(password_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    GtkWidget *eye_reg_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eye_reg_eventbox), "eye_password");
    gtk_box_pack_start(GTK_BOX(password_reg_box), eye_reg_eventbox, FALSE, FALSE, 5);
    gtk_widget_set_size_request(GTK_WIDGET(eye_reg_eventbox), 35, 30);
    gtk_widget_set_valign(GTK_WIDGET(eye_reg_eventbox), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(eye_reg_eventbox), "button_press_event",
        G_CALLBACK(eye_pressed), password_reg);

    // Entry to confirm a password during registration
    GtkWidget *password_reg_confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(password_reg_confirm_box), "password_eye_back");
    gtk_widget_set_margin_start(GTK_WIDGET(password_reg_confirm_box), 20);
    gtk_widget_set_margin_end(GTK_WIDGET(password_reg_confirm_box), 20);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg_confirm_box, FALSE, FALSE, 0);

    password_reg_confirm = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_reg_confirm), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg_confirm), "password_reg_confirm");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg_confirm), 335, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg_confirm), text_for_labels[24]);
    gtk_box_pack_start(GTK_BOX(password_reg_confirm_box), password_reg_confirm, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(password_reg_confirm), "changed",
        G_CALLBACK(data_change_registration_event), NULL);
    
    GtkWidget *eye_reg_confirm_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eye_reg_confirm_eventbox), "eye_password");
    gtk_box_pack_start(GTK_BOX(password_reg_confirm_box), eye_reg_confirm_eventbox, FALSE, FALSE, 5);
    gtk_widget_set_size_request(GTK_WIDGET(eye_reg_confirm_eventbox), 35, 30);
    gtk_widget_set_valign(GTK_WIDGET(eye_reg_confirm_eventbox), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(eye_reg_confirm_eventbox), "button_press_event",
        G_CALLBACK(eye_pressed), password_reg_confirm);

    // Inscription fail
    gtk_box_pack_start(GTK_BOX(registration_menu_1), fail_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(fail_inscription), "error");

    // Back button
    GtkWidget *registration_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_buttons_box, TRUE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(registration_buttons_box), GTK_ALIGN_END);
    GtkWidget *back_btn = gtk_event_box_new();
    GtkWidget *back_btn_label = gtk_label_new(text_for_labels[15]);
    gtk_container_add(GTK_CONTAINER(back_btn), back_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box), back_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn), 100, 40);

    g_signal_connect(G_OBJECT(back_btn), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn), "button_press_event",
        G_CALLBACK(hide_registration_click), fail_auto_inscription);

    // Next button
    next_btn = gtk_event_box_new();
    GtkWidget *next_btn_label = gtk_label_new(text_for_labels[25]);
    gtk_container_add(GTK_CONTAINER(next_btn), next_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box), next_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(next_btn), "back_button");
    gtk_widget_set_opacity(GTK_WIDGET(next_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(next_btn), 100, 40);

    g_signal_connect(G_OBJECT(next_btn), "enter-notify-event",
        G_CALLBACK(next_btn_enter_notify), password_reg_confirm);
    g_signal_connect(G_OBJECT(next_btn), "leave-notify-event",
        G_CALLBACK(next_btn_leave_notify), password_reg_confirm);
    g_signal_connect(G_OBJECT(next_btn), "button_press_event",
        G_CALLBACK(transition_registration_click), fail_inscription);
    //=================================================================================
    

    // Registration menu page 2
    //=================================================================================
    registration_menu_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), registration_menu_2, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(registration_menu_2), 420, 400);

    // Inscription Registration
    GtkWidget *registration_inscription_2 = gtk_label_new(text_for_labels[21]);
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_inscription_2, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription_2), "authorization");

    // Entry for a first name
    firstname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(firstname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(firstname_reg), 400, 50);
    gtk_widget_set_margin_top(GTK_WIDGET(firstname_reg), 35);
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstname_reg), text_for_labels[26]);
    gtk_box_pack_start(GTK_BOX(registration_menu_2), firstname_reg, FALSE, FALSE, 0);

    // Entry for a second name
    secondname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(secondname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(secondname_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(secondname_reg), text_for_labels[27]);
    gtk_box_pack_start(GTK_BOX(registration_menu_2), secondname_reg, FALSE, FALSE, 0);

    // Back button
    GtkWidget *registration_buttons_box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_buttons_box_2), "registration_buttons_box_2");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_buttons_box_2, FALSE, FALSE, 90);
    GtkWidget *back_btn_2 = gtk_event_box_new();
    GtkWidget *back_btn_label_2 = gtk_label_new(text_for_labels[15]);
    gtk_container_add(GTK_CONTAINER(back_btn_2), back_btn_label_2);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box_2), back_btn_2, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn_2), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn_2), 100, 40);

    g_signal_connect(G_OBJECT(back_btn_2), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn_2), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn_2), "button_press_event",
        G_CALLBACK(hide_registration_click_2), fail_inscription);

    // Finish button
    GtkWidget *finish_btn = gtk_event_box_new();
    GtkWidget *finish_btn_label = gtk_label_new(text_for_labels[28]);
    gtk_container_add(GTK_CONTAINER(finish_btn), finish_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box_2), finish_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(finish_btn), "back_button");
    gtk_widget_set_opacity(GTK_WIDGET(finish_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(finish_btn), 100, 40);

    g_signal_connect(G_OBJECT(finish_btn), "enter-notify-event",
        G_CALLBACK(activate_prelight_with_condition_entry), firstname_reg);
    g_signal_connect(G_OBJECT(finish_btn), "leave-notify-event",
        G_CALLBACK(deactivate_prelight_with_condition_entry), firstname_reg);
    g_signal_connect(G_OBJECT(finish_btn), "button_press_event",
        G_CALLBACK(authorization_after_registration), fail_auto_inscription);

    g_signal_connect(G_OBJECT(firstname_reg), "changed",
        G_CALLBACK(data_change_registration_event_2), finish_btn);
    //=================================================================================

    gtk_widget_show_all(GTK_WIDGET(authorization_area));
    gtk_widget_hide(GTK_WIDGET(chat_area));
    gtk_widget_hide(GTK_WIDGET(registration_menu_1));
    gtk_widget_hide(GTK_WIDGET(fail_inscription));
    gtk_widget_hide(GTK_WIDGET(fail_auto_inscription));
    gtk_widget_hide(GTK_WIDGET(registration_menu_2));
}
