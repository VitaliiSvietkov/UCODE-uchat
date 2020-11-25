#include "../inc/uchat_client.h"

void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area, 
    GtkWidget **messages, GtkWidget **contacts, GtkWidget **settings) {

    *content_selection_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 48);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 8);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), CUR_WIDTH / 3 + 50, 24);

    *messages = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(*messages), "draw",
                     G_CALLBACK(mx_draw_event_messages), NULL);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), *messages, TRUE, FALSE, 22);
    gtk_widget_set_size_request(GTK_WIDGET(*messages), 24, 24);

    *contacts = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(*contacts), "draw",
                     G_CALLBACK(mx_draw_event_contacts), NULL);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), *contacts, TRUE, FALSE, 30);
    gtk_widget_set_size_request(GTK_WIDGET(*contacts), 21, 24);

    *settings = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(*settings), "draw",
                     G_CALLBACK(mx_draw_event_settings), NULL);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), *settings, TRUE, FALSE, 22);
    gtk_widget_set_size_request(GTK_WIDGET(*settings), 24, 24);
}
