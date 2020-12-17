#include "../../inc/uchat_client.h"

void mx_configure_main_area(void) {
     
    main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), main_area);
    gtk_widget_set_size_request(GTK_WIDGET(main_area), CUR_WIDTH, CUR_HEIGHT);

    chat_area = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), chat_area, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(chat_area), CUR_WIDTH, CUR_HEIGHT);
    g_signal_connect(chat_area, "key-press-event", G_CALLBACK(room_close), NULL);

    authorization_area = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), authorization_area, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(authorization_area), CUR_WIDTH, CUR_HEIGHT);

    GtkWidget *background = gtk_drawing_area_new();
    gtk_fixed_put(GTK_FIXED(chat_area), background, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(background), CUR_WIDTH, CUR_HEIGHT);
    g_signal_connect(G_OBJECT(background), "draw",
                     G_CALLBACK(mx_draw_event_background), NULL);
    
    /*
    GdkPixbufAnimation *anim = gdk_pixbuf_animation_new_from_file("client/img/standard/giphy.gif", NULL);
    GtkWidget *gif = gtk_image_new_from_animation(anim);
    gtk_fixed_put(GTK_FIXED(main_area), gif, 100, 100);
    */

    GtkWidget *label = gtk_label_new(text_for_labels[4]);
    gtk_widget_set_name(GTK_WIDGET(label), "DefaultLabel");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_fixed_put(GTK_FIXED(chat_area), label, CUR_WIDTH - CUR_WIDTH / 2.5 - 50, CUR_HEIGHT / 2 - 20);
    labels_head = mx_label_create_node(label, 4);

    // Create a header for left area
    mx_configure_left_header();
}
