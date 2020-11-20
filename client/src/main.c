#include "../inc/uchat_client.h"

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);
  GdkPixbuf *icon = mx_create_pixbuf("client/img/logo.png");
  mx_init_window(window, icon);

  // Create a main area where all widgets will be shown
  GtkWidget *main_area = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), main_area);

  // Create the right area
  GtkWidget *right_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(main_area), right_field);

  // Create the left area
  GtkWidget *left_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(main_area), left_area);

  // Create a background
  GtkWidget *background = gtk_drawing_area_new();
  gtk_fixed_put(GTK_FIXED(main_area), background, 0, 0);
  gtk_widget_set_size_request(background, CUR_WIDTH, CUR_HEIGHT);
  g_signal_connect(G_OBJECT(background), "draw", G_CALLBACK(mx_on_draw_event_background), NULL);

  gtk_widget_show_all (window);
  
  g_object_unref(icon); //in fact, a "free" command
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("VsvietkovTeam.UCODE.UchatApplication",
                                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
