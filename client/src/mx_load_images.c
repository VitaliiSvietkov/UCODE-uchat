#include "../inc/uchat_client.h"

void mx_load_images(void) {
    t_settings.standard = gtk_image_new_from_file("client/img/settings-standard.png");
    t_messages.standard = gtk_image_new_from_file("client/img/messages-standard.png");
    t_contacts.standard = gtk_image_new_from_file("client/img/contacts-standard.png");
    
    gtk_image_set_pixel_size(GTK_IMAGE(t_settings.standard), 30);
    gtk_image_set_pixel_size(GTK_IMAGE(t_messages.standard), 30);
    gtk_image_set_pixel_size(GTK_IMAGE(t_contacts.standard), 30);

    t_img_event_box.messages_box = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_img_event_box.messages_box), 40, 30);
    gtk_container_add(GTK_CONTAINER(t_img_event_box.messages_box), t_messages.standard);
    t_img_event_box.contacts_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.contacts_box), t_contacts.standard);
    t_img_event_box.settings_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.settings_box), t_settings.standard);
}
