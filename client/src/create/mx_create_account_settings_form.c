#include "../../inc/uchat_client.h"

void mx_create_account_settings_form(void) {
    gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    // Blackout with main container
    //==================================================================================
    blackout = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(blackout), "blackout");
    gtk_fixed_put(GTK_FIXED(chat_area), blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout), CUR_WIDTH, CUR_HEIGHT);

    GtkWidget *account_settings_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(account_settings_container), "edit_user_form");
    gtk_container_add(GTK_CONTAINER(blackout), account_settings_container);
    gtk_widget_set_valign(GTK_WIDGET(account_settings_container), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(account_settings_container), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(account_settings_container), 300, 300);

    g_signal_connect(G_OBJECT(blackout), "button_press_event",
        G_CALLBACK(blackout_destroy), account_settings_container);
    //==================================================================================

    // "close" image
    //==================================================================================
    GtkWidget *close_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(account_settings_container), close_image_box, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
    //==================================================================================

    // Main area
    //==================================================================================
    
    //==================================================================================
    gtk_widget_show_all(GTK_WIDGET(blackout));
}
