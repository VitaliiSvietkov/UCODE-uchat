#include "../inc/uchat_client.h"

void mx_load_images(void) {
    t_settings.standard = NULL;
    t_messages.standard = NULL;
    t_contacts.standard = NULL;

    t_settings.standard = gtk_image_new_from_file("client/img/settings-standard.png");
    t_messages.standard = gtk_image_new_from_file("client/img/messages-standard.png");
    t_contacts.standard = gtk_image_new_from_file("client/img/contacts-standard.png");
    t_contacts.hovered = gtk_image_new_from_file("client/img/contacts-hovered.png");
}
