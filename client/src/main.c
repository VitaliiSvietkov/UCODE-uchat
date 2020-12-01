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
    main_area = NULL;
    GtkWidget *left_header = NULL;
    GtkWidget *content_selection_area = NULL;
    GtkWidget *chat_enter_area = NULL;
    chats_list = NULL;
    settings_menu = NULL;

    GtkWidget *entry_search = NULL;
    GtkWidget *entry_chat = NULL;

    // Drawing areas
    GtkWidget *background = NULL;
  
    gtk_init(&argc, &argv);

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/css/uchat.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    mx_load_images();
  
    // Create a new window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    mx_init_window(&window);

    // Create a main area where all widgets will be shown
    mx_configure_main_area(&main_area, &background, &window);

    // Create a header for left area
    mx_configure_left_header(&left_header, &main_area, &entry_search);

    // Create a selection area
    mx_configure_content_selection_area(&content_selection_area, &main_area);

    // Create a chat enter area
    mx_configure_chat_enter_area(&chat_enter_area, &main_area, &entry_chat);

    // Create a chat list area
    chats_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(main_area), chats_list, 0, 95);
    active_leftbar_container = chats_list;

    // Create a contacts list area
    contacts_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(main_area), contacts_list, 0, 95);

    // Create a settings menu
    mx_configure_settings_menu_area(&settings_menu, &main_area);

    g_signal_connect(window, "configure-event", G_CALLBACK(test), NULL);

    gtk_widget_show_all (window);
    // Hide unneccessary widgets
    gtk_widget_hide(GTK_WIDGET(tick_image.box));
    gtk_widget_hide(GTK_WIDGET(contacts_list));
    gtk_widget_hide(GTK_WIDGET(settings_menu));
    // Return sensativity for entries
    gtk_widget_set_sensitive(GTK_WIDGET(entry_search), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_chat), TRUE);


    gtk_main();
  
    return 0;
}
