#include "../inc/uchat_client.h"

gboolean test(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    CUR_WIDTH = event->configure.width;
    CUR_HEIGHT = event->configure.height;
    //gtk_widget_queue_resize(GTK_WIDGET(widget));
    gtk_widget_queue_draw(GTK_WIDGET(widget));
    if (user_data) {}
    return FALSE;
}

int main(int argc, char *argv[]) {
    // Containers
    GtkWidget *window = NULL;
    GtkWidget *main_area = NULL;
    GtkWidget *left_header = NULL;
    GtkWidget *content_selection_area = NULL;
    GtkWidget *chat_enter_area = NULL;

    GdkPixbuf *icon = NULL;
    GtkWidget *entry_search = NULL;

    // Drawing areas
    GtkWidget *background = NULL;
    GtkWidget *settings = NULL;
    GtkWidget *messages = NULL;
    GtkWidget *contacts = NULL;
    //GtkWidget *more = NULL;
    mx_load_images();
  
    gtk_init(&argc, &argv);
  
    // Create a new window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    mx_init_window(&window, &icon);
    icon = mx_create_pixbuf("client/img/logo.png");

    // Create a main area where all widgets will be shown
    mx_configure_main_area(&main_area, &background, &window);
    // Create a header for left area
    mx_configure_left_header(&left_header, &main_area, &entry_search);
    // Create a selection area
    mx_configure_content_selection_area(&content_selection_area, &main_area, 
        &messages, &contacts, &settings);
    // Create a chat enter area
    mx_configure_chat_enter_area(&chat_enter_area, &main_area);

    g_signal_connect(window, "configure-event", G_CALLBACK(test), NULL);

    gtk_widget_show_all (window);

    gtk_main();
  
    g_object_unref(icon); //in fact, a "free" command
    mx_free_images();
    return 0;
}
