#include "../inc/uchat_client.h"

/*
void do_drawing(cairo_t *cr) {
    cairo_set_source_surface(cr, t_settings.standard, 38, 48);
    cairo_paint(cr);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr);
    if (widget) {}
    if (user_data) {}
    return FALSE;
} */

int main(int argc, char *argv[]) {
  GtkWidget *window;
  
  gtk_init(&argc, &argv);
  
  // Create a new window
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  GdkPixbuf *icon = mx_create_pixbuf("client/img/logo.png");
  mx_init_window(window, icon);

  // Create a main area where all widgets will be shown
  GtkWidget *main_area = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), main_area);
  
  // Create the right area
  GtkWidget *right_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  //gtk_container_add(GTK_CONTAINER(main_area), right_field);
  gtk_fixed_put(GTK_FIXED(main_area), right_field, 0, 0);
  
  /*
  // Create the left area
  GtkWidget *left_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(main_area), left_area);*/

  // Create a background
  GtkWidget *background = gtk_drawing_area_new();
  gtk_fixed_put(GTK_FIXED(main_area), background, 0, 0);
  gtk_widget_set_size_request(background, CUR_WIDTH, CUR_HEIGHT);
  g_signal_connect(G_OBJECT(background), "draw", G_CALLBACK(mx_on_draw_event_background), NULL);

  gtk_widget_show_all (window);
  
  gtk_main();
  
  g_object_unref(icon); //in fact, a "free" command

  return 0;
}

