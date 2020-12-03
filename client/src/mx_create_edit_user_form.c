#include "../inc/uchat_client.h"

void mx_create_edit_user_form() {
    // Create a blackout - a dark background behind the form
    //==================================================================================
    back_blackout = gtk_event_box_new();
    GtkWidget *blackout_background = gtk_fixed_new();
    gtk_widget_set_name(GTK_WIDGET(back_blackout), "back_blackout");
    gtk_widget_set_state_flags(GTK_WIDGET(back_blackout), GTK_STATE_FLAG_NORMAL, TRUE);
    g_signal_connect(G_OBJECT(back_blackout), "button_press_event",
        G_CALLBACK(blackout_click), NULL);
    gtk_container_add(GTK_CONTAINER(back_blackout), blackout_background);
    gtk_fixed_put(GTK_FIXED(main_area), back_blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout_background), CUR_WIDTH, CUR_HEIGHT);
    //==================================================================================


    edit_user_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_form), 400, 520);
    gtk_widget_set_name(GTK_WIDGET(edit_user_form), "edit_user_form");
    gtk_fixed_put(GTK_FIXED(blackout_background), edit_user_form,
        CUR_WIDTH / 3 - 10, CUR_HEIGHT / 5 - 50);


    // "close" image
    //==================================================================================
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
    //==================================================================================

    // "change avatar" field
    //==================================================================================
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 100, 100);
    gtk_box_pack_start(GTK_BOX(edit_user_form), avatar, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(mx_draw_event_avatar), (int*)100);

    GtkWidget *change_avatar_btn = gtk_button_new_with_label("Change photo");
    gtk_box_pack_start(GTK_BOX(edit_user_form), change_avatar_btn, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(change_avatar_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(change_avatar_btn), GTK_RELIEF_NONE);
    gtk_widget_set_halign(GTK_WIDGET(change_avatar_btn), GTK_ALIGN_CENTER);

    g_signal_connect(G_OBJECT(change_avatar_btn), "clicked",
        G_CALLBACK(change_avatart_btn_click), NULL);

    //==================================================================================

    // "change name" field
    //==================================================================================
    edit_username_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(edit_username_eventbox), "edit_eventbox");
    gtk_widget_set_size_request(GTK_WIDGET(edit_username_eventbox), 400, 40);
    gtk_box_pack_start(GTK_BOX(edit_user_form), edit_username_eventbox, FALSE, FALSE, 0);
    GtkWidget *edit_username_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_username_box), 400, 0);
    gtk_container_add(GTK_CONTAINER(edit_username_eventbox), edit_username_box);
    edit_username_icon = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_username_icon), "edit_username_icon");
    gtk_widget_set_size_request(GTK_WIDGET(edit_username_icon), 30, 30);
    gtk_widget_set_valign(GTK_WIDGET(edit_username_icon), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(edit_username_box), edit_username_icon, FALSE, FALSE, 20);
    
    char *username_tmp = strdup(t_user.FirstName);
    username_tmp = mx_strjoin(username_tmp, " ");
    username_tmp = mx_strjoin(username_tmp, t_user.SecondName);
    GtkWidget *edit_username_label = gtk_label_new(username_tmp);
    free(username_tmp);

    gtk_box_pack_start(GTK_BOX(edit_username_box), edit_username_label, FALSE, FALSE, 20);
    gtk_widget_set_halign(GTK_WIDGET(edit_username_label), GTK_ALIGN_CENTER);
    gtk_widget_set_name(GTK_WIDGET(edit_username_label), "edit_label");

    GtkWidget *edit_username_pen = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_username_pen), "pen");
    gtk_widget_set_size_request(GTK_WIDGET(edit_username_pen), 20, 20);
    gtk_widget_set_valign(GTK_WIDGET(edit_username_pen), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(edit_username_pen), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(edit_username_box), edit_username_pen, TRUE, TRUE, 20);

    g_signal_connect(G_OBJECT(edit_username_eventbox), "enter-notify-event",
        G_CALLBACK(edit_username_eventbox_enter_notify_event), edit_username_pen);
    g_signal_connect(G_OBJECT(edit_username_eventbox), "leave-notify-event",
        G_CALLBACK(edit_username_eventbox_leave_notify_event), edit_username_pen);
    //g_signal_connect(G_OBJECT(edit_username_eventbox), "button_press_event",
    //    G_CALLBACK(edit_username_eventbox_click_event), NULL);
    //==================================================================================

    // "change pseudo" field
    //==================================================================================
    edit_pseudo_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_eventbox), "edit_eventbox");
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_eventbox), 400, 40);
    gtk_box_pack_start(GTK_BOX(edit_user_form), edit_pseudo_eventbox, FALSE, FALSE, 0);
    GtkWidget *edit_pseudo_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_box), 400, 0);
    gtk_container_add(GTK_CONTAINER(edit_pseudo_eventbox), edit_pseudo_box);
    edit_pseudo_icon = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_icon), "edit_pseudo_icon");
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_icon), 30, 30);
    gtk_widget_set_valign(GTK_WIDGET(edit_pseudo_icon), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(edit_pseudo_box), edit_pseudo_icon, FALSE, FALSE, 20);

    GtkWidget *edit_pseudo_label = gtk_label_new(t_user.pseudonim);

    gtk_box_pack_start(GTK_BOX(edit_pseudo_box), edit_pseudo_label, FALSE, FALSE, 20);
    gtk_widget_set_halign(GTK_WIDGET(edit_pseudo_label), GTK_ALIGN_CENTER);
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_label), "edit_label");

    GtkWidget *edit_pseudo_pen = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_pen), "pen");
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_pen), 20, 20);
    gtk_widget_set_valign(GTK_WIDGET(edit_pseudo_pen), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(edit_pseudo_pen), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(edit_pseudo_box), edit_pseudo_pen, TRUE, TRUE, 20);

    g_signal_connect(G_OBJECT(edit_pseudo_eventbox), "enter-notify-event",
        G_CALLBACK(edit_pseudo_eventbox_enter_notify_event), edit_pseudo_pen);
    g_signal_connect(G_OBJECT(edit_pseudo_eventbox), "leave-notify-event",
        G_CALLBACK(edit_pseudo_eventbox_leave_notify_event), edit_pseudo_pen);
    //g_signal_connect(G_OBJECT(edit_pseudo_eventbox), "button_press_event",
    //    G_CALLBACK(edit_pseudo_eventbox_click_event), NULL);
    //==================================================================================

    // "change description" field
    //==================================================================================
    GtkWidget *change_description_label = gtk_label_new("Edit info about you:");
    gtk_widget_set_name(GTK_WIDGET(change_description_label), "change_description_label");
    gtk_box_pack_start(GTK_BOX(edit_user_form), change_description_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(change_description_label), GTK_ALIGN_START);

    GtkWidget *change_description_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(change_description_box), "change_description_box");
    gtk_box_pack_start(GTK_BOX(edit_user_form), change_description_box, FALSE, FALSE, 0);  
    GtkWidget *change_description_entry = gtk_text_view_new();
    gtk_widget_set_name(GTK_WIDGET(change_description_entry), "change_description_entry");
    gtk_box_pack_start(GTK_BOX(change_description_box), change_description_entry, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(change_description_entry), 400, 100);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(change_description_entry), GTK_WRAP_WORD);
    gtk_widget_set_state_flags(GTK_WIDGET(change_description_entry), GTK_STATE_FLAG_NORMAL, TRUE);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(change_description_entry));

    g_signal_connect(G_OBJECT(change_description_entry), "button_press_event",
        G_CALLBACK(gtk_widget_grab_focus), NULL);

    g_signal_connect(G_OBJECT(buffer), "changed",
        G_CALLBACK(change_description_entry_change_event), NULL);
    //gtk_entry_set_text(GTK_ENTRY(change_description_entry), t_user.description);
    //==================================================================================

    // Buttons to exit
    //==================================================================================
    GtkWidget *exit_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(edit_user_form), exit_buttons_box, FALSE, FALSE, 0);

    GtkWidget *commit_btn = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(commit_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(commit_btn), GTK_RELIEF_NONE);
    GtkWidget *exit_btn = gtk_button_new_with_label("Exit");
    gtk_widget_set_name(GTK_WIDGET(exit_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(exit_btn), GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(exit_buttons_box), exit_btn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(exit_buttons_box), commit_btn, TRUE, FALSE, 0);

    gtk_widget_set_size_request(GTK_WIDGET(commit_btn), 100, 0);
    gtk_widget_set_size_request(GTK_WIDGET(exit_btn), 100, 0);

    g_signal_connect(G_OBJECT(exit_btn), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
    //==================================================================================
}
