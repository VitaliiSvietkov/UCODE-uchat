#include "../inc/uchat_client.h"

void mx_configure_content_selection_area(GtkWidget **content_selection_area, GtkWidget **main_area) {
    // A container which contains section with images and a line just below it
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 48);

    GtkWidget *image_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(image_container), L_FIELD_WIDTH, 40);
    gtk_box_pack_start(GTK_BOX(*content_selection_area), image_container, TRUE, FALSE, 0);

    // A line which is under the images
    GtkWidget *delimiter = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(*content_selection_area), delimiter, TRUE, FALSE, 5);
    gtk_widget_set_size_request(GTK_WIDGET(delimiter), L_FIELD_WIDTH, 1);
    g_signal_connect(G_OBJECT(delimiter), "draw",
                     G_CALLBACK(mx_draw_event_delimiter), NULL);

    gtk_box_pack_start(GTK_BOX(image_container),
        t_img_event_box.messages_box, TRUE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(image_container),
        t_img_event_box.contacts_box, TRUE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(image_container),
        t_img_event_box.settings_box, TRUE, FALSE, 30);

    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "enter-notify-event",
        G_CALLBACK(messages_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "leave-notify-event",
        G_CALLBACK(messages_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "button_press_event",
        G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.contacts_box), "enter-notify-event",
        G_CALLBACK(contacts_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.contacts_box), "leave-notify-event",
        G_CALLBACK(contacts_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.contacts_box), "button_press_event",
        G_CALLBACK(contacts_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "enter-notify-event",
        G_CALLBACK(settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "leave-notify-event",
        G_CALLBACK(settings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "button_press_event",
        G_CALLBACK(settings_click), NULL);
}
