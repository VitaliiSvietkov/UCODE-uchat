#include "../../inc/uchat_client.h"

void mx_configure_message_enter_area(void) {
    // "message_enter_area" is a main container which defines background
    message_enter_area = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(message_enter_area), CUR_WIDTH - CUR_WIDTH / 3 - 50, 50);
    gtk_fixed_put(GTK_FIXED(chat_area), message_enter_area, L_FIELD_WIDTH, CUR_HEIGHT - 50);

    // "chat_container" is a pack with all widgets that will be used
    GtkWidget *chat_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(chat_container), CUR_WIDTH - CUR_WIDTH / 3 - 50, 30);
    gtk_container_set_border_width(GTK_CONTAINER(chat_container), 5);
    gtk_fixed_put(GTK_FIXED(message_enter_area), chat_container, 0, 3);
    g_signal_connect(G_OBJECT(message_enter_area), "draw",
        G_CALLBACK(mx_draw_event_message_enter_area), NULL);
    

    //gtk_box_pack_start(GTK_BOX(chat_container), t_img_event_box.add_box, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(chat_container), add_image.box, FALSE, FALSE, 8);

    GtkWidget *entry_chat = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(entry_chat), "entry");
    gtk_box_pack_start(GTK_BOX(chat_container), entry_chat, TRUE, TRUE, 8);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_chat), text_for_labels[14]);
    g_signal_connect(G_OBJECT(entry_chat), "changed", G_CALLBACK(entry_chat_fill_event), NULL);

    gtk_box_pack_start(GTK_BOX(chat_container), ban_image.box, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(chat_container), tick_image.box, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(chat_container), more_image.box, FALSE, FALSE, 8);

    g_signal_connect(G_OBJECT(add_image.box), "enter-notify-event",
        G_CALLBACK(activate_prelight), &add_image);
    g_signal_connect(G_OBJECT(add_image.box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    /*g_signal_connect(G_OBJECT(t_img_event_box.add_box), "button_press_event",
        G_CALLBACK(add_click), NULL);*/

    g_signal_connect(G_OBJECT(tick_image.box), "enter-notify-event",
        G_CALLBACK(activate_prelight), &tick_image);
    g_signal_connect(G_OBJECT(tick_image.box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);

    g_signal_connect(G_OBJECT(more_image.box), "enter-notify-event",
        G_CALLBACK(activate_prelight), &more_image);
    g_signal_connect(G_OBJECT(more_image.box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
}
