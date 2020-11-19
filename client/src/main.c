#include "../inc/uchat_client.h"

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

  GdkPixbuf *icon = mx_create_pixbuf("client/img/logo.png");

  // Create a background
  GtkWidget *background = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), background);
  g_signal_connect(G_OBJECT(background), "draw", G_CALLBACK(mx_on_draw_event_background), NULL);

  
  //Configure the window
  gtk_widget_set_size_request(window, WIN_WIDTH_MIN, WIN_HEIGHT_MIN); //sets the min size
  gtk_window_set_title(GTK_WINDOW(window), "UchatApp");
  gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH_MIN, WIN_HEIGHT_MIN); //sets the size the window will be shown
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_icon(GTK_WINDOW(window), icon);  


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
