#include "../../inc/uchat_client.h"

void mx_create_language_menu(void) {
    // Create a blackout - a dark background behind the form
    //==================================================================================
    blackout = gtk_event_box_new();
    GtkWidget *language_fixed_container = gtk_fixed_new();
    gtk_widget_set_name(GTK_WIDGET(blackout), "blackout");
    gtk_container_add(GTK_CONTAINER(blackout), language_fixed_container);
    gtk_fixed_put(GTK_FIXED(chat_area), blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(language_fixed_container), CUR_WIDTH, CUR_HEIGHT);
    //==================================================================================

    GtkWidget *language_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(language_form), "edit_user_form");
    gtk_fixed_put(GTK_FIXED(language_fixed_container), language_form,
        CUR_WIDTH / 3 - 10, CUR_HEIGHT / 5 + 75);

    g_signal_connect(G_OBJECT(blackout), "button_press_event",
        G_CALLBACK(blackout_destroy), language_form);
    

    // "close" image
    //==================================================================================
    GtkWidget *close_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
    gtk_widget_set_margin_bottom(GTK_WIDGET(close_image_box), 15);
    gtk_box_pack_start(GTK_BOX(language_form), close_image_box, FALSE, FALSE, 0);
    gtk_widget_set_state_flags(GTK_WIDGET(close_image_box), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
        G_CALLBACK(mx_language_close), NULL);
    //==================================================================================

    
    // Create and pack widgets
    gtk_box_pack_start(GTK_BOX(language_form),
        mx_language_create_box("client/img/USA.png", "English"),
        FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(language_form),
        mx_language_create_box("client/img/russia.png", "Русский"),
        FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(language_form),
        mx_language_create_box("client/img/ukraine.png", "Українська"),
        FALSE, FALSE, 0);

    gtk_widget_show_all(GTK_WIDGET(blackout));
}
