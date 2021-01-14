#include "../../inc/uchat_client.h"

GtkWidget *mx_create_room(char *gid) {
    char *cur_user_gid = mx_strdup(t_user.pseudonim);
    mx_sort_string(cur_user_gid);

    GtkWidget *eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eventbox), "eventbox_room");
    g_signal_connect(G_OBJECT(eventbox), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(room_click), gid);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(box), L_FIELD_WIDTH, 55);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    GtkWidget *avatar = NULL;
    GdkPixbuf *pixbuf = NULL;

    GtkWidget *title = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(title), "room_title");
    gtk_widget_set_margin_top(GTK_WIDGET(title), 5);
    GtkWidget *preview = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(preview), "room_text_preview");
    gtk_widget_set_margin_top(GTK_WIDGET(preview), 10);

    if (mx_strcmp(gid, cur_user_gid) == 0) {
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/bookmark.png", 40, 40);
        gtk_label_set_text(GTK_LABEL(title), "Saved Messages");
        gtk_label_set_text(GTK_LABEL(preview), "Lorem ipsum");
        avatar = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
        gtk_widget_set_size_request(GTK_WIDGET(avatar), 40, 40);
        gtk_widget_set_margin_start(GTK_WIDGET(avatar), 15);
        g_object_unref(pixbuf);
    }
    else {
        /* Load data from data base */
    }

    gtk_box_pack_start(GTK_BOX(box), avatar, FALSE, FALSE, 0);
    
    GtkWidget *v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_start(GTK_WIDGET(v_box), 15);
    gtk_box_pack_start(GTK_BOX(box), v_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), preview, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(preview), GTK_ALIGN_START);

    //free(gid);
    free(cur_user_gid);
    return eventbox;
}
