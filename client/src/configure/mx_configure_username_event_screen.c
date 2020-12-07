#include "../../inc/uchat_client.h"

void mx_configure_username_event_screen() {
    // Return image
    //==================================================================================
    GtkWidget *return_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(return_image_box), "return_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(return_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), return_image_box, FALSE, FALSE, 0);
    gtk_widget_set_state_flags(GTK_WIDGET(return_image_box), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_widget_set_halign(GTK_WIDGET(return_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(return_image_box), "enter-notify-event",
        G_CALLBACK(image_enter_notify), NULL);
    g_signal_connect(G_OBJECT(return_image_box), "leave-notify-event",
        G_CALLBACK(image_leave_notify), NULL);
    g_signal_connect(G_OBJECT(return_image_box), "button_press_event",
        G_CALLBACK(return_username_click_event), edit_username_event_screen);
    //==================================================================================

    // Draw avatar block
    //==================================================================================
    GtkWidget *username_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(username_avatar), 100, 100);
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), username_avatar, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(username_avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(username_avatar), "draw", G_CALLBACK(mx_draw_event_avatar), (int*)100);
    //==================================================================================

    // "change first name" block
    //==================================================================================
    GtkWidget *change_fname_label = gtk_label_new("Write your first name:");
    gtk_widget_set_name(GTK_WIDGET(change_fname_label), "edit_label");
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), change_fname_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(change_fname_label), GTK_ALIGN_START);
    gtk_widget_set_margin_top(GTK_WIDGET(change_fname_label), 30);

    change_fname_entry = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(change_fname_entry), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(change_fname_entry), TRUE);
    gtk_widget_set_name(GTK_WIDGET(change_fname_entry), "edit_entry");
    gtk_entry_set_text(GTK_ENTRY(change_fname_entry), NewFirstName);
    gtk_widget_set_size_request(GTK_WIDGET(change_fname_entry), 400, 0);
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), change_fname_entry, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(change_fname_entry), "changed",
        G_CALLBACK(fname_entry_changed_event), NULL);
    //==================================================================================

    // "change second name" block
    //==================================================================================
    GtkWidget *change_sname_label = gtk_label_new("Write your second name:");
    gtk_widget_set_name(GTK_WIDGET(change_sname_label), "edit_label");
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), change_sname_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(change_sname_label), GTK_ALIGN_START);

    change_sname_entry = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(change_sname_entry), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(change_sname_entry), TRUE);
    gtk_widget_set_name(GTK_WIDGET(change_sname_entry), "edit_entry");
    gtk_entry_set_text(GTK_ENTRY(change_sname_entry), NewSecondName);
    gtk_widget_set_size_request(GTK_WIDGET(change_sname_entry), 400, 0);
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), change_sname_entry, FALSE, FALSE, 0);
    //==================================================================================

    // Return buttons block
    //==================================================================================
    GtkWidget *return_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(edit_username_event_screen), return_buttons_box, FALSE, FALSE, 0);
    gtk_widget_set_margin_top(GTK_WIDGET(return_buttons_box), 100);

    GtkWidget *commit_username_btn = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(commit_username_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(commit_username_btn), GTK_RELIEF_NONE);
    GtkWidget *exit_username_btn = gtk_button_new_with_label("Back");
    gtk_widget_set_name(GTK_WIDGET(exit_username_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(exit_username_btn), GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(return_buttons_box), exit_username_btn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(return_buttons_box), commit_username_btn, TRUE, FALSE, 0);

    gtk_widget_set_size_request(GTK_WIDGET(commit_username_btn), 100, 0);
    gtk_widget_set_size_request(GTK_WIDGET(exit_username_btn), 100, 0);

    g_signal_connect(G_OBJECT(exit_username_btn), "button_press_event",
        G_CALLBACK(return_username_click_event), edit_username_event_screen);
    g_signal_connect(G_OBJECT(commit_username_btn), "button_press_event",
        G_CALLBACK(commit_username_click_event), edit_username_event_screen);
    //==================================================================================
}
