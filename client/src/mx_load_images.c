#include "../inc/uchat_client.h"

void mx_load_images(void) {
    messages_image.box = gtk_event_box_new();
    messages_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(messages_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(messages_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(messages_image.box), "messages_image");

    contacts_image.box = gtk_event_box_new();
    contacts_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(contacts_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(contacts_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(contacts_image.box), "contacts_image");

    settings_image.box = gtk_event_box_new();
    settings_image.active = true;
    gtk_widget_set_state_flags(GTK_WIDGET(settings_image.box), GTK_STATE_FLAG_CHECKED, TRUE);
    gtk_widget_set_valign(GTK_WIDGET(settings_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(settings_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(settings_image.box), "settings_image");

    edit_user_image.box = gtk_event_box_new();
    edit_user_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(edit_user_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(edit_user_image.box), "edit_user_image");

    account_settings_image.box = gtk_event_box_new();
    account_settings_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(account_settings_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(account_settings_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(account_settings_image.box), "edit_user_image");

    change_account_image.box = gtk_event_box_new();
    change_account_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(change_account_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(change_account_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(change_account_image.box), "change_account_image");

    chat_settings_image.box = gtk_event_box_new();
    chat_settings_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(chat_settings_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(chat_settings_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(chat_settings_image.box), "chat_settings_image");

    language_image.box = gtk_event_box_new();
    language_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(language_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(language_image.box), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(language_image.box), "language_image");


    t_active_image = &settings_image;
}
