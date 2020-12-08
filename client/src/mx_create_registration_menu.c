#include "../inc/uchat_client.h"

void mx_create_registration_menu() {
    //background
    back_black = gtk_event_box_new();
    GtkWidget *black_background = gtk_fixed_new();
    gtk_widget_set_name(GTK_WIDGET(back_black), "back_black");
    gtk_widget_set_state_flags(GTK_WIDGET(back_black), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_container_add(GTK_CONTAINER(back_black), black_background);
    gtk_fixed_put(GTK_FIXED(authorization_area), back_black, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(black_background), CUR_WIDTH, CUR_HEIGHT);

    //registration_menu
    main_autorization_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    log_in_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_autorization_menu), log_in_menu, FALSE, FALSE, 0);
    registration_menu_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_autorization_menu), registration_menu_1, FALSE, FALSE, 0);
    registration_menu_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_autorization_menu), registration_menu_2, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(main_autorization_menu), 400, 400);
    gtk_widget_set_name(GTK_WIDGET(main_autorization_menu), "registration_menu_form");
    gtk_fixed_put(GTK_FIXED(black_background), main_autorization_menu,
    CUR_WIDTH / 5 + 70, CUR_HEIGHT / 5);

    //inscription Log in
    GtkWidget *log_in_inscription = gtk_label_new("Autorization");
    gtk_box_pack_start(GTK_BOX(log_in_menu), log_in_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(log_in_inscription), "Autorization");

    //place to enter a login
    login = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login), "Enter an username");
    gtk_box_pack_start(GTK_BOX(log_in_menu), login, FALSE, FALSE, 0);

    //place to enter a password
    password = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password), "Enter a password");
    gtk_box_pack_start(GTK_BOX(log_in_menu), password, FALSE, FALSE, 0);
    
    //login button
    login_btn = gtk_event_box_new();
    GtkWidget *login_btn_label = gtk_label_new("Log in");
    gtk_container_add(GTK_CONTAINER(login_btn), login_btn_label);
    gtk_box_pack_start(GTK_BOX(log_in_menu), login_btn, FALSE, FALSE, 30);
    gtk_widget_set_name(GTK_WIDGET(login_btn), "login_button");
    gtk_widget_set_opacity(GTK_WIDGET(login_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(login_btn), 200, 50);
    gtk_widget_set_halign(GTK_WIDGET(login_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(login_btn), "enter-notify-event",
        G_CALLBACK(login_btn_enter_notify_event), NULL);
    g_signal_connect(G_OBJECT(login_btn), "leave-notify-event",
        G_CALLBACK(login_btn_leave_notify_event), NULL);

    g_signal_connect(G_OBJECT(password), "changed",
        G_CALLBACK(data_change_event), NULL);
    g_signal_connect(G_OBJECT(login), "changed",
        G_CALLBACK(data_change_event), NULL);

    g_signal_connect(G_OBJECT(login_btn), "button_press_event",
        G_CALLBACK(autorization), NULL);

    gtk_widget_unset_state_flags(GTK_WIDGET(login_btn), GTK_STATE_FLAG_PRELIGHT);

    //link registration
    GtkWidget *registration_link = gtk_event_box_new();
    GtkWidget *registration_lable = gtk_label_new("Follow this link to registration");
    gtk_container_add(GTK_CONTAINER(registration_link), registration_lable);
    gtk_box_pack_start(GTK_BOX(log_in_menu), registration_link, FALSE, FALSE, 10);
    gtk_widget_set_name(GTK_WIDGET(registration_link), "Registration");
    g_signal_connect(G_OBJECT(registration_link), "enter-notify-event",
        G_CALLBACK(registration_label_enter_notify_event), registration_lable);
    g_signal_connect(G_OBJECT(registration_link), "leave-notify-event",
        G_CALLBACK(registration_label_leave_notify_event), registration_lable);
    g_signal_connect(G_OBJECT(registration_link), "button_press_event",
        G_CALLBACK(hide_autorization_click), NULL);

    //                          REGISTRATION MENU PAGE 1   

    //inscription Registration
    GtkWidget *registration_inscription = gtk_label_new("Registration");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription), "Autorization");
    
    //place to enter a login during registration
    login_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(login_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(login_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(login_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_reg), "Enter an username");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), login_reg, FALSE, FALSE, 0);

    //place to enter a password during registration
    password_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg), "Enter a password");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg, FALSE, FALSE, 0);

    //place to confirm a password during registration
    password_reg_confirm = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(password_reg_confirm), TRUE);
    gtk_widget_set_name(GTK_WIDGET(password_reg_confirm), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(password_reg_confirm), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_reg_confirm), "Enter a password again");
    gtk_box_pack_start(GTK_BOX(registration_menu_1), password_reg_confirm, FALSE, FALSE, 0);

    //back button
    GtkWidget *registration_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(registration_menu_1), registration_buttons_box, FALSE, FALSE, 60);
    back_btn = gtk_event_box_new();
    GtkWidget *back_btn_label = gtk_label_new("Back");
    gtk_container_add(GTK_CONTAINER(back_btn), back_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box), back_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn), 100, 40);

    g_signal_connect(G_OBJECT(back_btn), "enter-notify-event",
        G_CALLBACK(back_btn_enter_notify_event), NULL);
    g_signal_connect(G_OBJECT(back_btn), "leave-notify-event",
        G_CALLBACK(back_btn_leave_notify_event), NULL);

    g_signal_connect(G_OBJECT(back_btn), "button_press_event",
        G_CALLBACK(hide_registration_click), NULL);

    //next button
    next_btn = gtk_event_box_new();
    GtkWidget *next_btn_label = gtk_label_new("Next");
    gtk_container_add(GTK_CONTAINER(next_btn), next_btn_label);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box), next_btn, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(next_btn), "back_button");
    gtk_widget_set_opacity(GTK_WIDGET(next_btn), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(next_btn), 100, 40);

    g_signal_connect(G_OBJECT(next_btn), "enter-notify-event",
        G_CALLBACK(next_btn_enter_notify_event), NULL);
    g_signal_connect(G_OBJECT(next_btn), "leave-notify-event",
        G_CALLBACK(next_btn_leave_notify_event), NULL);

    g_signal_connect(G_OBJECT(login_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);
    g_signal_connect(G_OBJECT(password_reg), "changed",
        G_CALLBACK(data_change_registration_event), NULL);
    g_signal_connect(G_OBJECT(password_reg_confirm), "changed",
        G_CALLBACK(data_change_registration_event), NULL);

    gtk_widget_unset_state_flags(GTK_WIDGET(next_btn), GTK_STATE_FLAG_PRELIGHT);

    g_signal_connect(G_OBJECT(next_btn), "button_press_event",
        G_CALLBACK(transition_registration_click), NULL);


     //                          REGISTRATION MENU PAGE 2 
    //inscription Registration
    GtkWidget *registration_inscription_2 = gtk_label_new("Registration");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_inscription_2, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(registration_inscription_2), "Autorization");

    //place to enter a firstname during registration
    firstname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(firstname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(firstname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(firstname_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstname_reg), "Enter a firstname");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), firstname_reg, FALSE, FALSE, 0);

    //place to enter a secondname during registration
    secondname_reg = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(secondname_reg), TRUE);
    gtk_widget_set_name(GTK_WIDGET(secondname_reg), "entry_data");
    gtk_widget_set_size_request(GTK_WIDGET(secondname_reg), 400, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(secondname_reg), "Enter a secondname");
    gtk_box_pack_start(GTK_BOX(registration_menu_2), secondname_reg, FALSE, FALSE, 0);

    //back button
    GtkWidget *registration_buttons_box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(registration_menu_2), registration_buttons_box_2, FALSE, FALSE, 90);
    back_btn_2 = gtk_event_box_new();
    GtkWidget *back_btn_label_2 = gtk_label_new("Back");
    gtk_container_add(GTK_CONTAINER(back_btn_2), back_btn_label_2);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box_2), back_btn_2, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(back_btn_2), "back_button");
    gtk_widget_set_size_request(GTK_WIDGET(back_btn_2), 100, 40);

    g_signal_connect(G_OBJECT(back_btn_2), "enter-notify-event",
        G_CALLBACK(back_btn_enter_notify_event_2), NULL);
    g_signal_connect(G_OBJECT(back_btn_2), "leave-notify-event",
        G_CALLBACK(back_btn_leave_notify_event_2), NULL);

    g_signal_connect(G_OBJECT(back_btn_2), "button_press_event",
        G_CALLBACK(hide_registration_click_2), NULL);

    //next button
    next_btn_2 = gtk_event_box_new();
    GtkWidget *next_btn_label_2 = gtk_label_new("Finish");
    gtk_container_add(GTK_CONTAINER(next_btn_2), next_btn_label_2);
    gtk_box_pack_start(GTK_BOX(registration_buttons_box_2), next_btn_2, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(next_btn_2), "back_button");
    gtk_widget_set_opacity(GTK_WIDGET(next_btn_2), 0.5);
    gtk_widget_set_size_request(GTK_WIDGET(next_btn_2), 100, 40);

    g_signal_connect(G_OBJECT(next_btn_2), "enter-notify-event",
        G_CALLBACK(next_btn_enter_notify_event_2), NULL);
    g_signal_connect(G_OBJECT(next_btn_2), "leave-notify-event",
        G_CALLBACK(next_btn_leave_notify_event_2), NULL);

    g_signal_connect(G_OBJECT(firstname_reg), "changed",
        G_CALLBACK(data_change_registration_event_2), NULL);

    gtk_widget_unset_state_flags(GTK_WIDGET(next_btn_2), GTK_STATE_FLAG_PRELIGHT);

    g_signal_connect(G_OBJECT(next_btn_2), "button_press_event",
        G_CALLBACK(autorization_after_registration), NULL);
}
