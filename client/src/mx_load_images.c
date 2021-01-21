#include "../inc/uchat_client.h"

void mx_load_images(void) {
    messages_image.box = gtk_event_box_new();
    messages_image.active = false;
    gtk_widget_set_valign(GTK_WIDGET(messages_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(messages_image.box), L_FIELD_WIDTH / 2 + 1, 55);
    gtk_widget_set_name(GTK_WIDGET(messages_image.box), "messages_image");

    settings_image.box = gtk_event_box_new();
    settings_image.active = true;
    gtk_widget_set_state_flags(GTK_WIDGET(settings_image.box), GTK_STATE_FLAG_CHECKED, TRUE);
    gtk_widget_set_valign(GTK_WIDGET(settings_image.box), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(settings_image.box), L_FIELD_WIDTH / 2, 55);
    gtk_widget_set_name(GTK_WIDGET(settings_image.box), "settings_image");

    edit_user_image = gtk_event_box_new();
    gtk_widget_set_valign(GTK_WIDGET(edit_user_image), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_image), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(edit_user_image), "edit_user_image");

    change_account_image = gtk_event_box_new();
    gtk_widget_set_valign(GTK_WIDGET(change_account_image), GTK_ALIGN_END);
    gtk_widget_set_size_request(GTK_WIDGET(change_account_image), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(change_account_image), "change_account_image");

    chat_settings_image = gtk_event_box_new();
    gtk_widget_set_valign(GTK_WIDGET(chat_settings_image), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(chat_settings_image), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(chat_settings_image), "chat_settings_image");

    language_image = gtk_event_box_new();
    gtk_widget_set_valign(GTK_WIDGET(language_image), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(language_image), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(language_image), "language_image");


    t_active_image = &settings_image;
}
