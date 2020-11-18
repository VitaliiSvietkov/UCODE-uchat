#include "../inc/uchat_client.h"

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  GdkPixbuf *icon = create_pixbuf("client/logo.png");
  
  //Configure the window
  gtk_window_set_title(GTK_WINDOW(window), "UchatApp");
  gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH_MIN, WIN_HEIGHT_MIN);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  
  gtk_widget_show (window);
  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);
  g_object_unref(icon);
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("VsvietkovTeam.UCODE.UchatApplication",
                                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
