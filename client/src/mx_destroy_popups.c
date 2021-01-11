#include "../inc/uchat_client.h"

void mx_destroy_popups(void) {
    if (tools_menu != NULL) {
        gdk_seat_ungrab(gdk_display_get_default_seat(gdk_display_get_default()));
        gtk_widget_destroy(GTK_WIDGET(tools_menu));
        tools_menu = NULL;
        //selected_msg_widget = NULL;
    }
    if (more_box != NULL) {
        gtk_widget_destroy(GTK_WIDGET(more_box));
        more_box = NULL;
        more_image.active = false;
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_PRELIGHT);
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_CHECKED);
    }
}
