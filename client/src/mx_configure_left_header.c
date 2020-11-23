#include "../inc/uchat_client.h"

void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, 
    GtkWidget **settings, GtkWidget **entry_search) {
    *left_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *left_header, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*left_header), 8);
    gtk_widget_set_size_request(GTK_WIDGET(*left_header), CUR_WIDTH / 3 + 50, 23);
  
    *settings = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(*settings), "draw",
                     G_CALLBACK(mx_draw_event_settings), NULL);
    gtk_box_pack_start(GTK_BOX(*left_header), *settings, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(*settings), 24, 23);

    *entry_search = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(*left_header), *entry_search, TRUE, TRUE, 0);
    //gtk_entry_set_has_frame(GTK_ENTRY(*entry_search), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(*entry_search), "Search...");
    
}