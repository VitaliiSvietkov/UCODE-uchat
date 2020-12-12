#include "../../inc/uchat_client.h"

void mx_create_edit_user_form(void) {
     
    // Create a blackout - a dark background behind the form
    //==================================================================================
    blackout = gtk_event_box_new();
    GtkWidget *edit_user_fixed_container = gtk_fixed_new();
    gtk_widget_set_name(GTK_WIDGET(blackout), "blackout");
    gtk_widget_set_state_flags(GTK_WIDGET(blackout), GTK_STATE_FLAG_NORMAL, TRUE);
    g_signal_connect(G_OBJECT(blackout), "button_press_event",
        G_CALLBACK(blackout_click), NULL);
    gtk_container_add(GTK_CONTAINER(blackout), edit_user_fixed_container);
    gtk_fixed_put(GTK_FIXED(chat_area), blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_fixed_container), CUR_WIDTH, CUR_HEIGHT);
    //==================================================================================

    NewFirstName = strdup(t_user.FirstName);
    if (t_user.SecondName != NULL)
        NewSecondName = strdup(t_user.SecondName);
    else
        NewSecondName = strdup("");
    NewPseudonim = strdup(t_user.pseudonim);
    NewDescription = strdup(t_user.description);
    NewAvatar = gdk_pixbuf_copy(t_user.avatar);
    
    edit_user_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_user_form), "edit_user_form");
    gtk_fixed_put(GTK_FIXED(edit_user_fixed_container), edit_user_form,
        CUR_WIDTH / 3 - 10, CUR_HEIGHT / 5 - 50);

    edit_user_main_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_size_request(GTK_WIDGET(edit_user_form), 400, 520);
    gtk_box_pack_start(GTK_BOX(edit_user_form), edit_user_main_screen, FALSE, FALSE, 0);

    edit_username_event_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_size_request(GTK_WIDGET(edit_username_event_screen), 440, 500);
    gtk_box_pack_start(GTK_BOX(edit_user_form), edit_username_event_screen, FALSE, FALSE, 0);
    mx_configure_username_event_screen();

    edit_pseudonim_event_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudonim_event_screen), 440, 500);
    gtk_box_pack_start(GTK_BOX(edit_user_form), edit_pseudonim_event_screen, FALSE, FALSE, 0);
    mx_configure_pseudonim_event_screen();


    // "close" image
    //==================================================================================
    GtkWidget *close_image_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(close_image_box), "close_image_box");
    gtk_widget_set_size_request(GTK_WIDGET(close_image_box), 25, 25);
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), close_image_box, FALSE, FALSE, 0);
    gtk_widget_set_state_flags(GTK_WIDGET(close_image_box), GTK_STATE_FLAG_NORMAL, TRUE);
    gtk_widget_set_halign(GTK_WIDGET(close_image_box), GTK_ALIGN_START);

    g_signal_connect(G_OBJECT(close_image_box), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(close_image_box), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
    //==================================================================================

    // "change avatar" field
    //==================================================================================
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 100, 100);
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), avatar, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(mx_draw_event_image_avatar), &NewAvatar);

    GtkWidget *change_avatar_btn = gtk_button_new_with_label(text_for_labels[-1 + 6]);
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), change_avatar_btn, FALSE, FALSE, 0);
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
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), edit_username_eventbox, FALSE, FALSE, 0);
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
    edit_username_label = gtk_label_new(username_tmp);
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
        G_CALLBACK(edit_username_eventbox_enter_notify), edit_username_pen);
    g_signal_connect(G_OBJECT(edit_username_eventbox), "leave-notify-event",
        G_CALLBACK(edit_username_eventbox_leave_notify), edit_username_pen);
    g_signal_connect(G_OBJECT(edit_username_eventbox), "button_press_event",
        G_CALLBACK(edit_eventbox_click_event), edit_username_event_screen);
    //==================================================================================

    // "change pseudo" field
    //==================================================================================
    edit_pseudo_eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_eventbox), "edit_eventbox");
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_eventbox), 400, 40);
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), edit_pseudo_eventbox, FALSE, FALSE, 0);
    GtkWidget *edit_pseudo_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_box), 400, 0);
    gtk_container_add(GTK_CONTAINER(edit_pseudo_eventbox), edit_pseudo_box);
    edit_pseudo_icon = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(edit_pseudo_icon), "edit_pseudo_icon");
    gtk_widget_set_size_request(GTK_WIDGET(edit_pseudo_icon), 30, 30);
    gtk_widget_set_valign(GTK_WIDGET(edit_pseudo_icon), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(edit_pseudo_box), edit_pseudo_icon, FALSE, FALSE, 20);

    edit_pseudo_label = gtk_label_new(t_user.pseudonim);

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
        G_CALLBACK(edit_pseudo_eventbox_enter_notify), edit_pseudo_pen);
    g_signal_connect(G_OBJECT(edit_pseudo_eventbox), "leave-notify-event",
        G_CALLBACK(edit_pseudo_eventbox_leave_notify), edit_pseudo_pen);
    g_signal_connect(G_OBJECT(edit_pseudo_eventbox), "button_press_event",
        G_CALLBACK(edit_eventbox_click_event), edit_pseudonim_event_screen);
    //==================================================================================

    // "change description" field
    //==================================================================================
    GtkWidget *change_description_label = gtk_label_new(text_for_labels[6]);
    gtk_widget_set_name(GTK_WIDGET(change_description_label), "edit_label");
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), change_description_label, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(change_description_label), GTK_ALIGN_START);

    GtkWidget *change_description_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(change_description_box), "change_description_box");
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), change_description_box, FALSE, FALSE, 0);  
    GtkWidget *change_description_entry = gtk_text_view_new();
    gtk_widget_set_name(GTK_WIDGET(change_description_entry), "change_description_entry");
    gtk_box_pack_start(GTK_BOX(change_description_box), change_description_entry, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(change_description_entry), 400, 100);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(change_description_entry), GTK_WRAP_WORD);
    gtk_widget_set_state_flags(GTK_WIDGET(change_description_entry), GTK_STATE_FLAG_NORMAL, TRUE);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(change_description_entry));
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), 
        t_user.description, strlen(t_user.description));

    g_signal_connect(G_OBJECT(change_description_entry), "button_press_event",
        G_CALLBACK(gtk_widget_grab_focus), NULL);

    g_signal_connect(G_OBJECT(buffer), "changed",
        G_CALLBACK(change_description_entry_change_event), NULL);
    //==================================================================================

    // Buttons to exit
    //==================================================================================
    GtkWidget *exit_buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(edit_user_main_screen), exit_buttons_box, FALSE, FALSE, 0);

    GtkWidget *commit_btn = gtk_button_new_with_label(text_for_labels[12]);
    gtk_widget_set_name(GTK_WIDGET(commit_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(commit_btn), GTK_RELIEF_NONE);

    GtkWidget *exit_btn = gtk_button_new_with_label(text_for_labels[11]);
    gtk_widget_set_name(GTK_WIDGET(exit_btn), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(exit_btn), GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(exit_buttons_box), exit_btn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(exit_buttons_box), commit_btn, TRUE, FALSE, 0);

    gtk_widget_set_size_request(GTK_WIDGET(commit_btn), 100, 0);
    gtk_widget_set_size_request(GTK_WIDGET(exit_btn), 100, 0);

    g_signal_connect(G_OBJECT(exit_btn), "button_press_event",
        G_CALLBACK(close_image_click_event), NULL);
    g_signal_connect(G_OBJECT(commit_btn), "button_press_event",
        G_CALLBACK(commit_edit_user_click_event), NULL);
    //==================================================================================
}
