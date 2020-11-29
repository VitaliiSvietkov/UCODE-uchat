#include "../inc/uchat_client.h"

void mx_configure_left_header(GtkWidget **left_header, GtkWidget **main_area, 
    GtkWidget **entry_search) {
    *left_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *left_header, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*left_header), 8);
    gtk_widget_set_size_request(GTK_WIDGET(*left_header), L_FIELD_WIDTH, 23);

    *entry_search = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(*left_header), *entry_search, TRUE, TRUE, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(*entry_search), "Search...");
}
