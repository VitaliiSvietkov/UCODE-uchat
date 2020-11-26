#include "../inc/uchat_client.h"

void mx_configure_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window) {
    *main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *main_area);
    gtk_widget_set_size_request(GTK_WIDGET(*main_area), CUR_WIDTH, CUR_HEIGHT);

    *background = gtk_drawing_area_new();
    gtk_fixed_put(GTK_FIXED(*main_area), *background, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(*background), CUR_WIDTH, CUR_HEIGHT);
    g_signal_connect(G_OBJECT(*background), "draw",
                     G_CALLBACK(mx_draw_event_background), NULL);
    
    GtkWidget *label = gtk_label_new("Select a chat to start conversation...");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_fixed_put(GTK_FIXED(*main_area), label, CUR_WIDTH - CUR_WIDTH / 2.5, CUR_HEIGHT / 2);

    //gtk_fixed_put(GTK_FIXED(*main_area), more_img, 200, 100);
    //gtk_image_set_pixel_size(GTK_IMAGE(more_img), 24);
}
