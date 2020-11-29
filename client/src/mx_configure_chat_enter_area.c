#include "../inc/uchat_client.h"

void mx_configure_chat_enter_area(GtkWidget **chat_enter_area, GtkWidget **main_area,
    GtkWidget **entry_chat) {
    *chat_enter_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *chat_enter_area, L_FIELD_WIDTH, CUR_HEIGHT - 40);
    gtk_widget_set_size_request(GTK_WIDGET(*chat_enter_area), CUR_WIDTH - CUR_WIDTH / 3 - 50, 40);
    g_signal_connect(G_OBJECT(*chat_enter_area), "draw",
                     G_CALLBACK(mx_draw_event_chat_enter_area), NULL);
    
    gtk_box_pack_start(GTK_BOX(*chat_enter_area), t_img_event_box.add_box, FALSE, FALSE, 8);

    *entry_chat = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(*chat_enter_area), *entry_chat, TRUE, TRUE, 8);
    gtk_entry_set_placeholder_text(GTK_ENTRY(*entry_chat), "Write a message...");
    g_signal_connect(G_OBJECT(*entry_chat), "changed", G_CALLBACK(entry_chat_fill_event), NULL);

    gtk_box_pack_start(GTK_BOX(*chat_enter_area), t_img_event_box.ban_box, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(*chat_enter_area), t_img_event_box.tick_box, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(*chat_enter_area), t_img_event_box.more_box, FALSE, FALSE, 8);

    g_signal_connect(G_OBJECT(t_img_event_box.add_box), "enter-notify-event",
        G_CALLBACK(add_enter_notify), &add_img);
    g_signal_connect(G_OBJECT(t_img_event_box.add_box), "leave-notify-event",
        G_CALLBACK(add_leave_notify), NULL);
    /*g_signal_connect(G_OBJECT(t_img_event_box.add_box), "button_press_event",
        G_CALLBACK(add_click), NULL);*/

    g_signal_connect(G_OBJECT(t_img_event_box.tick_box), "enter-notify-event",
        G_CALLBACK(tick_enter_notify), &tick_img);
    g_signal_connect(G_OBJECT(t_img_event_box.tick_box), "leave-notify-event",
        G_CALLBACK(tick_leave_notify), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.more_box), "enter-notify-event",
        G_CALLBACK(more_enter_notify), &more_img);
    g_signal_connect(G_OBJECT(t_img_event_box.more_box), "leave-notify-event",
        G_CALLBACK(more_leave_notify), NULL);
}
