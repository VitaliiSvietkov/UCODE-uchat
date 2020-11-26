#include "../inc/uchat_client.h"

void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area,
    GtkWidget **entry_chat) {
    *chat_enter_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *chat_enter_area, CUR_WIDTH / 3 + 50, CUR_HEIGHT - 40);
    gtk_widget_set_size_request(GTK_WIDGET(*chat_enter_area), CUR_WIDTH - CUR_WIDTH / 3 - 50, 40);
    g_signal_connect(G_OBJECT(*chat_enter_area), "draw",
                     G_CALLBACK(mx_draw_event_chat_enter_area), NULL);
    
    *entry_chat = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(*chat_enter_area), *entry_chat, TRUE, TRUE, 8);
    //gtk_entry_set_has_frame(GTK_ENTRY(*entry_chat), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(*entry_chat), "Search...");
}
