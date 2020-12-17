#include "../../inc/uchat_client.h"

void mx_create_chat_area(void) {
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_HEIGHT - 50, 100, 100, CUR_HEIGHT - 50);
    right_container = gtk_scrolled_window_new(NULL, vadjustment);
    gtk_widget_set_size_request(GTK_WIDGET(right_container), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_fixed_put(GTK_FIXED(chat_area), right_container, L_FIELD_WIDTH, 0);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "chat_background");
    gtk_widget_set_size_request(GTK_WIDGET(box), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_container_add(GTK_CONTAINER(right_container), box);

    gtk_widget_show_all(GTK_WIDGET(right_container));
}
