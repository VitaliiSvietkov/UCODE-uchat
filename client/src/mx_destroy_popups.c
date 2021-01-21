#include "../inc/uchat_client.h"

void mx_destroy_popups(void) {
    if (tools_menu != NULL) {
        gdk_seat_ungrab(gdk_display_get_default_seat(gdk_display_get_default()));
        gtk_widget_destroy(GTK_WIDGET(tools_menu));
        tools_menu = NULL;
    }
    if (error_revealer != NULL) {
        gtk_container_forall(GTK_CONTAINER(error_revealer), (GtkCallback)gtk_widget_destroy, NULL);
        gtk_widget_destroy(GTK_WIDGET(error_revealer));
        error_revealer = NULL;
    }
    if (search_menu != NULL) {
        gdk_seat_ungrab(gdk_display_get_default_seat(gdk_display_get_default()));
        gtk_widget_destroy(GTK_WIDGET(search_menu));
        search_menu = NULL;
    }
    if (t_chat_room_vars.more_box != NULL) {
        gtk_widget_destroy(GTK_WIDGET(t_chat_room_vars.more_box));
        t_chat_room_vars.more_box = NULL;
        GList *children = gtk_container_get_children(GTK_CONTAINER(t_chat_room_vars.message_enter_area));
        gtk_widget_unset_state_flags(GTK_WIDGET(g_list_nth_data(children, 4)), 
            GTK_STATE_FLAG_PRELIGHT);
        gtk_widget_unset_state_flags(GTK_WIDGET(g_list_nth_data(children, 4)), 
            GTK_STATE_FLAG_CHECKED);
        g_list_free(children);
    }
}
