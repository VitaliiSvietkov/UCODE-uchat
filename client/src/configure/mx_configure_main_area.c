#include "../../inc/uchat_client.h"

//static void pop_up_close(GtkWidget *widget);

void mx_configure_main_area(void) {
     
    main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), main_area);
    gtk_widget_set_size_request(GTK_WIDGET(main_area), CUR_WIDTH, CUR_HEIGHT);

    /*
    GtkWidget *chat_eventbox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(main_area), chat_eventbox, 0, 0);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_eventbox), FALSE);
    g_signal_connect(G_OBJECT(chat_eventbox), "button_press_event", 
        G_CALLBACK(pop_up_close), NULL);
    */

    chat_area = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), chat_area, 0, 0);
    //gtk_container_add(GTK_CONTAINER(chat_eventbox), chat_area);
    gtk_widget_set_size_request(GTK_WIDGET(chat_area), CUR_WIDTH, CUR_HEIGHT);
    g_signal_connect(G_OBJECT(chat_area), "key-press-event", G_CALLBACK(room_close), NULL);

    authorization_area = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), authorization_area, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(authorization_area), CUR_WIDTH, CUR_HEIGHT);
}
/*
static void pop_up_close(GtkWidget *widget) {
    if (tools_menu != NULL) {
        gtk_widget_destroy(GTK_WIDGET(tools_menu));
        tools_menu = NULL;
    }
    if (more_box != NULL) {
        gtk_widget_destroy(GTK_WIDGET(more_box));
        more_box = NULL;
        more_image.active = false;
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_PRELIGHT);
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_CHECKED);
    }
}
*/
