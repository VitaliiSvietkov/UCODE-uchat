#include "../inc/uchat_client.h"

void mx_create_edit_user_form() {
    // Create a blackout
    back_blackout = gtk_event_box_new();
    GtkWidget *blackout_background = gtk_fixed_new();
    gtk_widget_set_name(GTK_WIDGET(back_blackout), "back_blackout");
    gtk_widget_set_state_flags(GTK_WIDGET(back_blackout), GTK_STATE_FLAG_NORMAL, TRUE);
    /*
    g_signal_connect(G_OBJECT(back_blackout), "button_press_event",
        G_CALLBACK(blackout_click), NULL);
    g_signal_connect(G_OBJECT(back_blackout), "leave-notify-event",
        G_CALLBACK(blackout_leave_notify_event), NULL);
    */
    gtk_container_add(GTK_CONTAINER(back_blackout), blackout_background);
    gtk_fixed_put(GTK_FIXED(main_area), back_blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout_background), CUR_WIDTH, CUR_HEIGHT);


    edit_user_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_form), 400, 400);
    gtk_widget_set_name(GTK_WIDGET(edit_user_form), "edit_user_form");
    gtk_fixed_put(GTK_FIXED(blackout_background), edit_user_form,
        CUR_WIDTH / 3, CUR_HEIGHT / 5);

    GtkWidget *close_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(edit_user_form), close_image_box, FALSE, FALSE, 0);
    gtk_widget_set_state_flags(GTK_WIDGET(close_image_box), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
        G_CALLBACK(close_image_enter_notify_event), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
        G_CALLBACK(close_image_leave_notify_event), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
}
