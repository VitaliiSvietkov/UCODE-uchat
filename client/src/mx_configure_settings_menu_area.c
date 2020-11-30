#include "../inc/uchat_client.h"

void mx_configure_settings_menu_area(GtkWidget **settings_menu, GtkWidget **main_area) {
    *settings_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(*settings_menu), L_FIELD_WIDTH, CUR_HEIGHT - 95);
    gtk_widget_set_name(GTK_WIDGET(*settings_menu), "settings_menu");

    gtk_fixed_put(GTK_FIXED(*main_area), *settings_menu, 0, 95);

    // Profile info section
    GtkWidget *user_profile_preview_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(user_profile_preview_eventbox), "user_profile_preview_eventbox");
    GtkWidget *user_profile_preview_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(user_profile_preview_box), "user_profile_preview_box");
    gtk_container_add(GTK_CONTAINER(user_profile_preview_eventbox), user_profile_preview_box);
    gtk_box_pack_start(GTK_BOX(*settings_menu), user_profile_preview_eventbox, FALSE, FALSE, 0);
    
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 70, 70);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(mx_draw_event_avatar), NULL);
    gtk_box_pack_start(GTK_BOX(user_profile_preview_box), avatar, FALSE, FALSE, 0);
    GtkWidget *user_info_preview = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(user_profile_preview_box), user_info_preview, FALSE, FALSE, 31);
    GtkWidget *username = gtk_label_new("Vitalii Svietkov");
    gtk_widget_set_name(GTK_WIDGET(username), "username_preview");
    GtkWidget *contact_info = gtk_label_new("a1vitalii.sv@gmail.com");
    gtk_widget_set_name(GTK_WIDGET(contact_info), "contact_info_preview");
    gtk_box_pack_start(GTK_BOX(user_info_preview), username, FALSE, FALSE, 0);
    gtk_widget_set_halign(username, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(user_info_preview), contact_info, FALSE, FALSE, 0);

    // "Edit profile" section
    GtkWidget *edit_user_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(edit_user_eventbox), "edit_user_eventbox");
    GtkWidget *edit_user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_user_box), "edit_user_box");
    gtk_container_add(GTK_CONTAINER(edit_user_eventbox), edit_user_box);
    gtk_box_pack_start(GTK_BOX(*settings_menu), edit_user_eventbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(edit_user_box), edit_user_img.standard, FALSE, FALSE, 0);
    GtkWidget *label_edit_user = gtk_label_new("Edit profile");
    gtk_widget_set_name(GTK_WIDGET(label_edit_user), "label_edit_user");
    gtk_box_pack_start(GTK_BOX(edit_user_box), label_edit_user, FALSE, FALSE, 50);

    // "Chat settings" section
    GtkWidget *chat_settings_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(chat_settings_eventbox), "chat_settings_eventbox");
    GtkWidget *chat_settings_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_settings_box), "chat_settings_box");
    gtk_container_add(GTK_CONTAINER(chat_settings_eventbox), chat_settings_box);
    gtk_box_pack_start(GTK_BOX(*settings_menu), chat_settings_eventbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_settings_box), chat_settings_img.standard, FALSE, FALSE, 0);
    GtkWidget *label_chat_settings = gtk_label_new("Chat settings");
    gtk_widget_set_name(GTK_WIDGET(label_chat_settings), "label_chat_settings");
    gtk_box_pack_start(GTK_BOX(chat_settings_box), label_chat_settings, FALSE, FALSE, 50);

    // "Language" section
    GtkWidget *language_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(language_eventbox), "language_eventbox");
    GtkWidget *language_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(language_box), "language_box");
    gtk_container_add(GTK_CONTAINER(language_eventbox), language_box);
    gtk_box_pack_start(GTK_BOX(*settings_menu), language_eventbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(language_box), language_img.standard, FALSE, FALSE, 0);
    GtkWidget *label_language = gtk_label_new("Language");
    gtk_widget_set_name(GTK_WIDGET(label_language), "label_language");
    gtk_box_pack_start(GTK_BOX(language_box), label_language, FALSE, FALSE, 50);

    // Footer section
    GtkWidget *label_impulse = gtk_label_new("Impulse");
    gtk_widget_set_name(GTK_WIDGET(label_impulse), "label_impulse");
    GtkWidget *label_version = gtk_label_new("Alpha version");
    gtk_widget_set_name(GTK_WIDGET(label_version), "label_version");
    gtk_box_pack_start(GTK_BOX(*settings_menu), label_impulse, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(*settings_menu), label_version, TRUE, TRUE, 0);

    gtk_widget_set_valign(GTK_WIDGET(label_impulse), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(label_version), GTK_ALIGN_END);

    g_signal_connect(G_OBJECT(edit_user_eventbox), "enter-notify-event",
        G_CALLBACK(edit_user_enter_notify), NULL);
    g_signal_connect(G_OBJECT(edit_user_eventbox), "leave-notify-event",
        G_CALLBACK(edit_user_leave_notify), NULL);

    g_signal_connect(G_OBJECT(chat_settings_eventbox), "enter-notify-event",
        G_CALLBACK(chat_settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(chat_settings_eventbox), "leave-notify-event",
        G_CALLBACK(chat_settings_leave_notify), NULL);

    g_signal_connect(G_OBJECT(language_eventbox), "enter-notify-event",
        G_CALLBACK(language_enter_notify), NULL);
    g_signal_connect(G_OBJECT(language_eventbox), "leave-notify-event",
        G_CALLBACK(language_leave_notify), NULL);
}
