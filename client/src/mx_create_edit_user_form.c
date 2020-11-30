#include "../inc/uchat_client.h"

void mx_create_edit_user_form() {
    // Create a blackout
    back_blackout = gtk_event_box_new();
    GtkWidget *blackout_background = gtk_fixed_new();
    g_signal_connect(G_OBJECT(blackout_background), "draw",
        G_CALLBACK(mx_draw_event_blackout), NULL);
    g_signal_connect(G_OBJECT(back_blackout), "button_press_event",
        G_CALLBACK(blackout_click), NULL);
    gtk_container_add(GTK_CONTAINER(back_blackout), blackout_background);
    gtk_fixed_put(GTK_FIXED(main_area), back_blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout_background), CUR_WIDTH, CUR_HEIGHT);

    edit_user_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_form), 400, 400);
    gtk_widget_set_name(GTK_WIDGET(edit_user_form), "edit_user_form");
    gtk_fixed_put(GTK_FIXED(blackout_background), edit_user_form,
        CUR_WIDTH / 3, CUR_HEIGHT / 5);
}
