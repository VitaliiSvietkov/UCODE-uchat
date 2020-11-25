#include "../inc/uchat_client.h"

void mx_init_window(GtkWidget **window, GdkPixbuf **icon) {
    CUR_WIDTH = WIN_WIDTH_MIN;
    CUR_HEIGHT = WIN_HEIGHT_MIN;
    // Configure the window
    gtk_window_set_resizable(GTK_WINDOW(*window), FALSE);
    gtk_widget_set_size_request(*window, WIN_WIDTH_MIN, WIN_HEIGHT_MIN); //sets the min size
    gtk_window_set_title(GTK_WINDOW(*window), "UchatApp");
    gtk_window_set_default_size(GTK_WINDOW(*window), WIN_WIDTH_MIN, WIN_HEIGHT_MIN); //sets the size the window will be shown
    gtk_window_set_position(GTK_WINDOW(*window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon(GTK_WINDOW(*window), *icon);
}
