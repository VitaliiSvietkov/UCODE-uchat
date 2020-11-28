#include "../inc/uchat_client.h"

void mx_load_images(void) {
    messages_img.active = true;
    messages_img.basic = "client/img/messages-standard.png";
    messages_img.hovered = "client/img/messages-standard-hovered.png";
    messages_img.standard = gtk_image_new_from_file(messages_img.hovered);

    settings_img.active = false;
    settings_img.basic = "client/img/settings-standard.png";
    settings_img.hovered = "client/img/settings-standard-hovered.png";
    settings_img.standard = gtk_image_new_from_file(settings_img.basic);

    contacts_img.active = false;
    contacts_img.basic = "client/img/contacts-standard.png";
    contacts_img.hovered = "client/img/contacts-standard-hovered.png";
    contacts_img.standard = gtk_image_new_from_file(contacts_img.basic);

    t_active = &messages_img;

    t_img_event_box.messages_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.messages_box), messages_img.standard);
    t_img_event_box.contacts_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.contacts_box), contacts_img.standard);
    t_img_event_box.settings_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.settings_box), settings_img.standard);
}
