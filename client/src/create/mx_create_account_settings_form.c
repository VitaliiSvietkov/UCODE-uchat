#include "../../inc/uchat_client.h"

void mx_create_account_settings_form(void) {
    gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    // Blackout with main container
    //==================================================================================
    blackout = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(blackout), "blackout");
    gtk_fixed_put(GTK_FIXED(chat_area), blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout), CUR_WIDTH, CUR_HEIGHT);

    GtkWidget *account_settings_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(account_settings_container), "edit_user_form");
    gtk_container_add(GTK_CONTAINER(blackout), account_settings_container);
    gtk_widget_set_valign(GTK_WIDGET(account_settings_container), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(account_settings_container), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(account_settings_container), 400, 400);

    g_signal_connect(G_OBJECT(blackout), "button_press_event",
        G_CALLBACK(blackout_destroy), account_settings_container);
    //==================================================================================

    // "close" image
    //==================================================================================
    GtkWidget *close_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(account_settings_container), close_image_box, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
    //==================================================================================

    // Account settings menu
    //==================================================================================
    account_settings_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(account_settings_container), account_settings_menu, FALSE, FALSE, 0);


    //Account settings inscription
    GtkWidget *account_settings_inscription = gtk_label_new(text_for_labels[34]);
    gtk_box_pack_start(GTK_BOX(account_settings_menu), account_settings_inscription, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(account_settings_inscription), "authorization");

    // "Password change" section
    //==============================================================================================
    GtkWidget *password_change_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(password_change_eventbox), "setting_menu_eventbox");
    GtkWidget *password_change_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(password_change_box), "change_box");
    gtk_container_add(GTK_CONTAINER(password_change_eventbox), password_change_box);
    gtk_box_pack_start(GTK_BOX(account_settings_menu), password_change_eventbox, FALSE, FALSE, 20);
    edit_password_change_icon = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_password_change_icon), "edit_pseudo_icon");
    gtk_widget_set_size_request(GTK_WIDGET(edit_password_change_icon), 30, 30);
    gtk_widget_set_valign(GTK_WIDGET(edit_password_change_icon), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(password_change_box), edit_password_change_icon, FALSE, FALSE, 20);
    
    //gtk_box_pack_start(GTK_BOX(password_change_box), edit_user_image.box, FALSE, FALSE, 0);

    GtkWidget *label_change_password = gtk_label_new(text_for_labels[35]);
    gtk_label_set_max_width_chars(GTK_LABEL(label_change_password), 10);
    gtk_widget_set_margin_start(GTK_WIDGET(label_change_password), 20);
    mx_label_push_back(&labels_head, label_change_password, 3);
    gtk_widget_set_name(GTK_WIDGET(label_change_password), "password_change_lable");
    gtk_box_pack_start(GTK_BOX(password_change_box), label_change_password, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(password_change_eventbox), "enter-notify-event",
        G_CALLBACK(password_change_enter_notify), NULL);
    g_signal_connect(G_OBJECT(password_change_eventbox), "leave-notify-event",
        G_CALLBACK(password_change_leave_notify), NULL);
    //g_signal_connect(G_OBJECT(edit_user_eventbox), "button_press_event",
    //    G_CALLBACK(edit_user_click), NULL);   
    //==============================================================================================

    // "Account settings" section
    //==============================================================================================
    /*GtkWidget *account_settings_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(account_settings_eventbox), "setting_menu_eventbox");
    GtkWidget *account_settings_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(account_settings_box), "change_box");
    gtk_container_add(GTK_CONTAINER(account_settings_eventbox), account_settings_box);
    gtk_box_pack_start(GTK_BOX(settings_menu), account_settings_eventbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(account_settings_box), account_settings_image.box, FALSE, FALSE, 0);

    GtkWidget *label_account_settings = gtk_label_new(text_for_labels[34]);
    gtk_label_set_max_width_chars(GTK_LABEL(label_account_settings), 16);
    gtk_widget_set_margin_start(GTK_WIDGET(label_account_settings), 50);
    mx_label_push_back(&labels_head, label_account_settings, 34);
    gtk_widget_set_name(GTK_WIDGET(label_account_settings), "label_settings_menu");
    gtk_box_pack_start(GTK_BOX(account_settings_box), label_account_settings, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(account_settings_eventbox), "enter-notify-event",
        G_CALLBACK(account_settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(account_settings_eventbox), "leave-notify-event",
        G_CALLBACK(account_settings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(account_settings_eventbox), "button_press_event",
        G_CALLBACK(account_settings_click), NULL);
        */
    //==============================================================================================


    //

    //==================================================================================
    gtk_widget_show_all(GTK_WIDGET(blackout));
}
