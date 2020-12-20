#include "../../inc/uchat_client.h"

void mx_create_attach_form(GtkWidget *entry, char *filename) {
    // Blackout with main container
    //==================================================================================
    blackout = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(blackout), "blackout");
    gtk_fixed_put(GTK_FIXED(chat_area), blackout, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(blackout), CUR_WIDTH, CUR_HEIGHT);

    GtkWidget *attach_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(attach_container), "attach_container");
    gtk_container_add(GTK_CONTAINER(blackout), attach_container);
    gtk_widget_set_valign(GTK_WIDGET(attach_container), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(attach_container), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(attach_container), 300, 300);

    g_signal_connect(G_OBJECT(blackout), "button_press_event",
        G_CALLBACK(blackout_destroy), attach_container);
    //==================================================================================

    // Image preview
    //==================================================================================
    GdkPixbuf *pixbuf = mx_get_pixbuf_with_size(filename, 300, 300);
    GtkWidget *image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
    g_object_unref(G_OBJECT(pixbuf));
    gtk_box_pack_start(GTK_BOX(attach_container), image, FALSE, FALSE, 0);
    //==================================================================================

    // Entry for a message
    //==================================================================================
    GtkWidget *message_entry = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(message_entry), "attach_entry");
    gtk_widget_set_size_request(GTK_WIDGET(message_entry), 300, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(message_entry), text_for_labels[14]);
    gtk_entry_set_text(GTK_ENTRY(message_entry), gtk_entry_get_text(GTK_ENTRY(entry)));
    gtk_box_pack_start(GTK_BOX(attach_container), message_entry, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(message_entry), "activate", G_CALLBACK(mx_attach_send_message_on_enter), filename);
    //==================================================================================

    gtk_widget_show_all(GTK_WIDGET(blackout));
}
