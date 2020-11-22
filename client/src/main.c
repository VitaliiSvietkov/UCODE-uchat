#include "../inc/uchat_client.h"

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    cairo_set_source_surface(cr, t_settings.standard, 0, 0);
    cairo_paint(cr);
    if (widget) {}
    if (user_data) {}
    return FALSE;
} 

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *main_area;
  
  GtkWidget *settings;
  t_settings.standard = cairo_image_surface_create_from_png("client/img/settings-standard.png");
  
  gtk_init(&argc, &argv);
  
  // Create a new window
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  GdkPixbuf *icon = mx_create_pixbuf("client/img/logo.png");
  mx_init_window(window, icon);

  // Create a main area where all widgets will be shown
  main_area = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), main_area);
  gtk_widget_set_size_request(GTK_WIDGET(main_area), CUR_WIDTH, CUR_HEIGHT);
  
  settings = gtk_drawing_area_new();
  gtk_fixed_put(GTK_FIXED(main_area), settings, 100, 0);
  gtk_widget_set_size_request(GTK_WIDGET(settings), CUR_WIDTH, CUR_HEIGHT);
  
  g_signal_connect(G_OBJECT(settings), "draw",
                   G_CALLBACK(on_draw_event), NULL);
  

  gtk_widget_show_all (window);
  gtk_widget_show(main_area);
  
  gtk_main();
  
  g_object_unref(icon); //in fact, a "free" command
  cairo_surface_destroy(t_settings.standard);
  return 0;
}

