#include "../inc/uchat_client.h"

void mx_load_images(void) {
    messages_img.active = true;
    messages_img.basic = "client/img/standard/messages-standard.png";
    messages_img.hovered = "client/img/standard/messages-standard-hovered.png";
    messages_img.standard = gtk_image_new_from_file(messages_img.hovered);

    settings_img.active = false;
    settings_img.basic = "client/img/standard/settings-standard.png";
    settings_img.hovered = "client/img/standard/settings-standard-hovered.png";
    settings_img.standard = gtk_image_new_from_file(settings_img.basic);

    contacts_img.active = false;
    contacts_img.basic = "client/img/standard/contacts-standard.png";
    contacts_img.hovered = "client/img/standard/contacts-standard-hovered.png";
    contacts_img.standard = gtk_image_new_from_file(contacts_img.basic);

    add_img.active = false;
    add_img.basic = "client/img/standard/add-standard.png";
    add_img.hovered = "client/img/standard/add-standard-hovered.png";
    add_img.standard = gtk_image_new_from_file(add_img.basic);

    ban_img.active = false;
    ban_img.basic = "client/img/standard/ban-standard.png";
    ban_img.hovered = NULL;
    ban_img.standard = gtk_image_new_from_file(ban_img.basic);
    gtk_widget_set_opacity(GTK_WIDGET(ban_img.standard), 0.7);

    tick_img.active = false;
    tick_img.basic = "client/img/standard/tick-standard.png";
    tick_img.hovered = "client/img/standard/tick-standard-hovered.png";
    tick_img.standard = gtk_image_new_from_file(tick_img.basic);

    more_img.active = false;
    more_img.basic = "client/img/standard/more-standard.png";
    more_img.hovered = "client/img/standard/more-standard-hovered.png";
    more_img.standard = gtk_image_new_from_file(more_img.basic);

    edit_user_img.active = false;
    edit_user_img.basic = "client/img/standard/edit-user-standard.png";
    edit_user_img.hovered = "client/img/standard/edit-user-standard-hovered.png";
    edit_user_img.standard = gtk_image_new_from_file(edit_user_img.basic);

    change_account_img.active = false;
    change_account_img.basic = "client/img/standard/identification-standard.png";
    change_account_img.hovered = "client/img/standard/identification-standard-hovered.png";
    change_account_img.standard = gtk_image_new_from_file(change_account_img.basic);

    chat_settings_img.active = false;
    chat_settings_img.basic = "client/img/standard/chat-settings-standard.png";
    chat_settings_img.hovered = "client/img/standard/chat-settings-standard-hovered.png";
    chat_settings_img.standard = gtk_image_new_from_file(chat_settings_img.basic);

    language_img.active = false;
    language_img.basic = "client/img/standard/book-standard.png";
    language_img.hovered = "client/img/standard/book-standard-hovered.png";
    language_img.standard = gtk_image_new_from_file(language_img.basic);

    t_active = &messages_img;

    t_img_event_box.messages_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.messages_box), messages_img.standard);
    t_img_event_box.contacts_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.contacts_box), contacts_img.standard);
    t_img_event_box.settings_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.settings_box), settings_img.standard);
    
    t_img_event_box.add_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.add_box), add_img.standard);
    t_img_event_box.ban_box = gtk_event_box_new();
    mx_tooltip("You cannot send an empty message!", t_img_event_box.ban_box);
    gtk_container_add(GTK_CONTAINER(t_img_event_box.ban_box), ban_img.standard);
    t_img_event_box.tick_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.tick_box), tick_img.standard);
    t_img_event_box.more_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.more_box), more_img.standard);
}
