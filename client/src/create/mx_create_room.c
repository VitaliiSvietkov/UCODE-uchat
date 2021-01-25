#include "../../inc/uchat_client.h"

GtkWidget *mx_create_room(unsigned int uid, gint width, 
    void (*func)(GtkWidget *, GdkEventButton *, gpointer)) {
        
    GtkWidget *eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eventbox), "eventbox_room");
    g_signal_connect(G_OBJECT(eventbox), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(*func), (gpointer)(uintptr_t)uid);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_margin_top(GTK_WIDGET(box), 5);
    gtk_widget_set_margin_bottom(GTK_WIDGET(box), 5);
    gtk_widget_set_size_request(GTK_WIDGET(box), width, 55);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    GtkWidget *avatar = NULL;
    GdkPixbuf *pixbuf = NULL;

    GtkWidget *title = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(title), "room_title");
    gtk_widget_set_margin_top(GTK_WIDGET(title), 5);
    GtkWidget *preview = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(preview), "room_text_preview");
    gtk_widget_set_margin_top(GTK_WIDGET(preview), 10);

    if (uid == 0) {
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/bookmark.png", 50, 50);
        gtk_label_set_text(GTK_LABEL(title), "Saved Messages");
        char *tmp_preview = "@";
        tmp_preview = mx_strjoin(tmp_preview, t_user.pseudonim);
        gtk_label_set_text(GTK_LABEL(preview), tmp_preview);
        free(tmp_preview);
        avatar = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
        gtk_widget_set_size_request(GTK_WIDGET(avatar), 50, 50);
        gtk_widget_set_margin_start(GTK_WIDGET(avatar), 15);
        g_object_unref(pixbuf);
    }
    else {
        // Load data from data base

        // Change for image read from server!!
        //mx_read_photo_from_bd((int)uid);
        //=====================================
        pixbuf = mx_get_pixbuf_with_size("client/img/avatar2.jpg", 50, 50);
        avatar = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
        gtk_widget_set_size_request(GTK_WIDGET(avatar), 50, 50);
        gtk_widget_set_margin_start(GTK_WIDGET(avatar), 15);
        g_object_unref(pixbuf);

        char sendBuff[256];
        bzero(sendBuff, 256);
        sprintf(sendBuff, "SendRoomData\n%d", uid);
        send(sockfd, sendBuff, 256, 0);
        
        char recvBuff[256];
        bzero(recvBuff, 256);
        recv(sockfd, recvBuff, 256, 0);

        char **recvData = mx_strsplit(recvBuff, '\n');
        gtk_label_set_text(GTK_LABEL(title), recvData[0]);
        gtk_label_set_text(GTK_LABEL(preview), recvData[1]);
        mx_del_strarr(&recvData);
    }
    gtk_box_pack_start(GTK_BOX(box), avatar, FALSE, FALSE, 0);
    
    GtkWidget *v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_start(GTK_WIDGET(v_box), 15);
    gtk_box_pack_start(GTK_BOX(box), v_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), title, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(v_box), preview, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(preview), GTK_ALIGN_START);

    return eventbox;
}
