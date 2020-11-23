#include "../inc/uchat_client.h"

void mx_free_images(void) {
    cairo_surface_destroy(t_settings.standard);
    cairo_surface_destroy(t_more.standard);
    cairo_surface_destroy(t_messages.standard);
    cairo_surface_destroy(t_contacts.standard);
}

void mx_load_images(void) {
    t_settings.standard = cairo_image_surface_create_from_png("client/img/settings-standard.png");
    t_more.standard = cairo_image_surface_create_from_png("client/img/more-standard.png");
    t_messages.standard = cairo_image_surface_create_from_png("client/img/messages-standard.png");
    t_contacts.standard = cairo_image_surface_create_from_png("client/img/contacts-standard.png");
}
