#include "../../inc/uchat_client.h"

void mx_configure_pseudonim_event_screen() {
    // Return image
    //==================================================================================
    GtkWidget *return_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(return_image_box), "return_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(return_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), return_image_box, FALSE, FALSE, 0);
    gtk_widget_set_state_flags(GTK_WIDGET(return_image_box), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_widget_set_halign(GTK_WIDGET(return_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(return_image_box), "enter-notify-event",
        G_CALLBACK(image_enter_notify), NULL);
    g_signal_connect(G_OBJECT(return_image_box), "leave-notify-event",
        G_CALLBACK(image_leave_notify), NULL);
    g_signal_connect(G_OBJECT(return_image_box), "button_press_event",
        G_CALLBACK(return_pseudonim_click_event), edit_pseudonim_event_screen);
    //==================================================================================

    // Draw avatar block
    //==================================================================================
    GtkWidget *pseudonim_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(pseudonim_avatar), 100, 100);
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), pseudonim_avatar, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(pseudonim_avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(pseudonim_avatar), "draw", G_CALLBACK(mx_draw_event_avatar), (int*)100);
    //==================================================================================

    // "change pseudonim" block
    //==================================================================================
    GtkWidget *change_pseudo_label = gtk_label_new("Write your new pseudonim:");
    gtk_widget_set_name(GTK_WIDGET(change_pseudo_label), "edit_label");
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), change_pseudo_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(change_pseudo_label), GTK_ALIGN_START);
    gtk_widget_set_margin_top(GTK_WIDGET(change_pseudo_label), 69);

    change_pseudo_entry = gtk_entry_new();
    gtk_widget_set_sensitive(GTK_WIDGET(change_pseudo_entry), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(change_pseudo_entry), TRUE);
    gtk_widget_set_name(GTK_WIDGET(change_pseudo_entry), "edit_entry");
    gtk_entry_set_text(GTK_ENTRY(change_pseudo_entry), NewPseudonim);
    gtk_widget_set_size_request(GTK_WIDGET(change_pseudo_entry), 400, 0);
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), change_pseudo_entry, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(change_pseudo_entry), "changed",
        G_CALLBACK(pseudo_entry_changed_event), NULL);
    //==================================================================================

    // Additional info block
    //==================================================================================
    GtkWidget *info_label = gtk_label_new("It will be easier for users to find you using this identifier.");
    gtk_widget_set_name(GTK_WIDGET(info_label), "info_label");
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), info_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(info_label), GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(info_label), TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(info_label), 380, 0);
    gtk_widget_set_margin_top(GTK_WIDGET(info_label), 0);
    //==================================================================================

    // Return buttons block
    //==================================================================================
    GtkWidget *return_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(edit_pseudonim_event_screen), return_buttons_box, FALSE, FALSE, 0);
    gtk_widget_set_margin_top(GTK_WIDGET(return_buttons_box), 100);

    GtkWidget *commit_pseudonim_btn = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(commit_pseudonim_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(commit_pseudonim_btn), GTK_RELIEF_NONE);
    GtkWidget *exit_pseudonim_btn = gtk_button_new_with_label("Back");
    gtk_widget_set_name(GTK_WIDGET(exit_pseudonim_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(exit_pseudonim_btn), GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(return_buttons_box), exit_pseudonim_btn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(return_buttons_box), commit_pseudonim_btn, TRUE, FALSE, 0);

    gtk_widget_set_size_request(GTK_WIDGET(commit_pseudonim_btn), 100, 0);
    gtk_widget_set_size_request(GTK_WIDGET(exit_pseudonim_btn), 100, 0);

    g_signal_connect(G_OBJECT(exit_pseudonim_btn), "button_press_event",
        G_CALLBACK(return_pseudonim_click_event), edit_pseudonim_event_screen);
    g_signal_connect(G_OBJECT(commit_pseudonim_btn), "button_press_event",
        G_CALLBACK(commit_pseudonim_click_event), edit_pseudonim_event_screen);
    //==================================================================================
}
