#include "../../inc/uchat_client.h"

GtkWidget *mx_create_room(int id) {
    GtkWidget *eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eventbox), "eventbox_room");
    g_signal_connect(G_OBJECT(eventbox), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(box), L_FIELD_WIDTH, 50);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    GtkWidget *avatar = gtk_drawing_area_new();
    GdkPixbuf *pixbuf = NULL;
    GtkWidget *title = gtk_label_new(NULL);
    GtkWidget *preview = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(avatar), "room_avatar");

    if (id == 0) {
        pixbuf = mx_get_pixbuf_with_size("client/img/ukraine.png", 40, 40);
        gtk_label_set_text(GTK_LABEL(title), "Saved Messages");
        gtk_label_set_text(GTK_LABEL(preview), "Lorem ipsum");
    }
    else {
        /* Load data from data base */
    }

    g_signal_connect(G_OBJECT(avatar), "draw",
        G_CALLBACK(mx_draw_event_round_image), &pixbuf);
    g_object_unref(pixbuf);

    gtk_box_pack_start(GTK_BOX(box), avatar, FALSE, FALSE, 0);
    
    GtkWidget *v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box), v_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), preview, FALSE, FALSE, 0);

    return eventbox;
}
