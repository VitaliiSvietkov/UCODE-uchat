#include "../inc/uchat_client.h"

int main(int argc, char *argv[]) {
    // Containers
    GtkWidget *window;
    GtkWidget *main_area = NULL;
    GtkWidget *left_header;

    GdkPixbuf *icon = NULL;

    // Drawing areas
    GtkWidget *background = NULL;
    GtkWidget *settings;
    mx_load_images();
  
    gtk_init(&argc, &argv);
  
    // Create a new window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    mx_init_window(window, icon);
    icon = mx_create_pixbuf("client/img/logo.png");

    // Create a main area where all widgets will be shown
    mx_configure_main_area(&main_area, &background, &window);

    // Create a header for left area
    left_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(main_area), left_header, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(left_header), 8);
    gtk_widget_set_size_request(GTK_WIDGET(left_header), CUR_WIDTH / 3 + 50 - 16, 23);
  
    settings = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(settings), "draw",
                     G_CALLBACK(mx_draw_event_settings), NULL);
    gtk_box_pack_start(GTK_BOX(left_header), settings, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(settings), 24, 23);
  

    gtk_widget_show_all (window);
    gtk_widget_show(main_area);
  
    gtk_main();
  
    g_object_unref(icon); //in fact, a "free" command
    mx_free_images();
    return 0;
}
