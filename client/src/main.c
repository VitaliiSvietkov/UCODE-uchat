#include "../inc/uchat_client.h"

int main(int argc, char *argv[]) {
    // Containers
    GtkWidget *window = NULL;
    GtkWidget *main_area = NULL;
    GtkWidget *left_header = NULL;
    GtkWidget *content_selection_area = NULL;

    GdkPixbuf *icon = NULL;
    GtkWidget *entry_search = NULL;

    // Drawing areas
    GtkWidget *background = NULL;
    GtkWidget *settings = NULL;
    GtkWidget *messages = NULL;
    GtkWidget *contacts = NULL;
    GtkWidget *more = NULL;
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
    mx_configure_left_header(&left_header, &main_area, &settings, &entry_search);
    // Create a selection area
    mx_configure_content_selection_area(&content_selection_area, &main_area, 
        &messages, &contacts, &more);

    gtk_widget_show_all (window);

    gtk_main();
  
    g_object_unref(icon); //in fact, a "free" command
    mx_free_images();
    return 0;
}
