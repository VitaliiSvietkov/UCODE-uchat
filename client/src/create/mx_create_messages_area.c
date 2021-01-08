#include "../../inc/uchat_client.h"

void mx_create_messages_area(void) {
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_HEIGHT - 50, 100, 100, CUR_HEIGHT - 50);
    right_container = gtk_scrolled_window_new(NULL, vadjustment);
    gtk_widget_set_size_request(GTK_WIDGET(right_container), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_fixed_put(GTK_FIXED(chat_area), right_container, L_FIELD_WIDTH, 0);
    messages_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(right_container), "chat_background");
    gtk_widget_set_size_request(GTK_WIDGET(messages_box), CUR_WIDTH - L_FIELD_WIDTH, CUR_HEIGHT - 50);
    gtk_container_add(GTK_CONTAINER(right_container), messages_box);

    GdkPixbuf *pixbuf = mx_create_pixbuf("client/img/avatar.jpg");
    pixbuf = mx_size_image_down(pixbuf);
    t_message *msg = mx_push_back_message(&curr_room_msg_head, mx_strdup("HELLOJDFOSF"), t_user.id, 
        pixbuf);
    mx_add_message(messages_box, msg);


    gtk_widget_show_all(GTK_WIDGET(right_container));
}
