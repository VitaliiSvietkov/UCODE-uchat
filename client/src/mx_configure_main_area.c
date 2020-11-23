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
}
