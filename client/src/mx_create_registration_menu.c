#include "../inc/uchat_client.h"

void mx_create_registration_menu(void) {
    // Background
    //=================================================================================
    authorization_fixed_container = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(authorization_area), authorization_fixed_container, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(authorization_fixed_container), CUR_WIDTH, CUR_HEIGHT);

    g_signal_connect(G_OBJECT(authorization_fixed_container), "draw",
        G_CALLBACK(mx_draw_event_authorization_fixed_container), NULL);
    //=================================================================================


    // Authorization menu
    //=================================================================================
    GtkWidget *main_authorization_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(main_authorization_menu), 400, 400);
    gtk_widget_set_name(GTK_WIDGET(main_authorization_menu), "registration_menu_form");
    gtk_fixed_put(GTK_FIXED(authorization_fixed_container), main_authorization_menu,
        CUR_WIDTH / 5 + 70, CUR_HEIGHT / 5);
    //=================================================================================


    // Log in menu
    //=================================================================================
    GtkWidget *log_in_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), log_in_menu, FALSE, FALSE, 0);

    // Inscription Log in
    GtkWidget *log_in_inscription = gtk_label_new("Authorization");
    gtk_box_pack_start(GTK_BOX(log_in_menu), log_in_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(log_in_inscription), "authorization");

    // Entry for login
    login = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login), "Your username:");
    gtk_box_pack_start(GTK_BOX(log_in_menu), login, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(login), "changed",
        G_CALLBACK(button_shine), NULL);

    // Entry for password
    GtkWidget *password_eye_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(log_in_menu), password_eye_box, FALSE, FALSE, 0);

    password = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password), 335, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password), "Your password:");
    gtk_box_pack_start(GTK_BOX(password_eye_box), password, FALSE, FALSE, 0);
    gtk_entry_set_visibility(GTK_ENTRY(password), FALSE);
    g_signal_connect(G_OBJECT(password), "changed",
        G_CALLBACK(button_shine), NULL);

    GtkWidget *eye_eventbox = gtk_event_box_new();
    GdkPixbuf *eye_pixbuf = mx_get_pixbuf_with_size("client/img/standard/eye.png", 40, 25);
    GtkWidget *eye = gtk_image_new_from_pixbuf(eye_pixbuf);
    g_object_unref(G_OBJECT(eye_pixbuf));
    gtk_container_add(GTK_CONTAINER(eye_eventbox), eye);
    gtk_box_pack_start(GTK_BOX(password_eye_box), eye_eventbox, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(eye), 40, 25);
    gtk_widget_set_valign(GTK_WIDGET(eye_eventbox), GTK_ALIGN_END);
    
    // Log in button
    login_btn = gtk_event_box_new();
    GtkWidget *login_btn_label = gtk_label_new("Log in");
    gtk_container_add(GTK_CONTAINER(login_btn), login_btn_label);
    gtk_box_pack_start(GTK_BOX(log_in_menu), login_btn, FALSE, FALSE, 30);
    gtk_widget_set_name(GTK_WIDGET(login_btn), "login_button");
    gtk_widget_set_opacity(GTK_WIDGET(login_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(login_btn), 200, 50);
    gtk_widget_set_halign(GTK_WIDGET(login_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(login_btn), "enter-notify-event",
        G_CALLBACK(login_btn_enter_notify), NULL);
    g_signal_connect(G_OBJECT(login_btn), "leave-notify-event",
        G_CALLBACK(login_btn_leave_notify), NULL);
    g_signal_connect(G_OBJECT(login_btn), "button_press_event",
        G_CALLBACK(authorization), NULL);

    // Link to registration
    GtkWidget *registration_link = gtk_event_box_new();
    GtkWidget *registration_lable = gtk_label_new("Follow this link to registration");
    gtk_container_add(GTK_CONTAINER(registration_link), registration_lable);
    gtk_box_pack_start(GTK_BOX(log_in_menu), registration_link, FALSE, FALSE, 10);
    gtk_widget_set_name(GTK_WIDGET(registration_link), "Registration");
    g_signal_connect(G_OBJECT(registration_link), "enter-notify-event",
        G_CALLBACK(activate_prelight), registration_lable);
    g_signal_connect(G_OBJECT(registration_link), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), registration_lable);
    g_signal_connect(G_OBJECT(registration_link), "button_press_event",
        G_CALLBACK(hide_authorization_click), log_in_menu);
    //=================================================================================

    // Registration menu page 1
    //=================================================================================
    registration_menu_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), registration_menu_1, FALSE, FALSE, 0);

    // Inscription Registration
    GtkWidget *registration_inscription = gtk_label_new("Registration");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription), "authorization");
    
    // Entry for a login during registration
    login_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_reg), "Enter an username");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), login_reg, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(login_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    // Entry for a password during registration
    password_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg), "Enter a password");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(password_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    // Entry to confirm a password during registration
    GtkWidget *password_reg_confirm = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg_confirm), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg_confirm), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg_confirm), "Enter a password again");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg_confirm, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(password_reg_confirm), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    // Back button
    GtkWidget *registration_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_buttons_box, FALSE, FALSE, 60);
    GtkWidget *back_btn = gtk_event_box_new();
    GtkWidget *back_btn_label = gtk_label_new("Back");
    gtk_container_add(GTK_CONTAINER(back_btn), back_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box), back_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn), 100, 40);

    g_signal_connect(G_OBJECT(back_btn), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn), "button_press_event",
        G_CALLBACK(hide_registration_click), log_in_menu);

    // Next button
    next_btn = gtk_event_box_new();
    GtkWidget *next_btn_label = gtk_label_new("Next");
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
        G_CALLBACK(transition_registration_click), NULL);
    //=================================================================================
    

    // Registration menu page 2
    //=================================================================================
    registration_menu_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_authorization_menu), registration_menu_2, FALSE, FALSE, 0);

    // Inscription Registration
    GtkWidget *registration_inscription_2 = gtk_label_new("Registration");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_inscription_2, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription_2), "authorization");

    // Entry for a first name
    GtkWidget *firstname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(firstname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(firstname_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstname_reg), "Enter a firstname");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), firstname_reg, FALSE, FALSE, 0);

    // Entry for a second name
    GtkWidget *secondname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(secondname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(secondname_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(secondname_reg), "Enter a secondname");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), secondname_reg, FALSE, FALSE, 0);

    // Back button
    GtkWidget *registration_buttons_box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_buttons_box_2, FALSE, FALSE, 90);
    GtkWidget *back_btn_2 = gtk_event_box_new();
    GtkWidget *back_btn_label_2 = gtk_label_new("Back");
    gtk_container_add(GTK_CONTAINER(back_btn_2), back_btn_label_2);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box_2), back_btn_2, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn_2), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn_2), 100, 40);

    g_signal_connect(G_OBJECT(back_btn_2), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn_2), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(back_btn_2), "button_press_event",
        G_CALLBACK(hide_registration_click_2), NULL);

    // Finish button
    finish_btn = gtk_event_box_new();
    GtkWidget *finish_btn_label = gtk_label_new("Finish");
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
        G_CALLBACK(authorization_after_registration), log_in_menu);

    g_signal_connect(G_OBJECT(firstname_reg), "changed",
        G_CALLBACK(data_change_registration_event_2), NULL);
    //=================================================================================
}
