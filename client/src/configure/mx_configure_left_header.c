#include "../../inc/uchat_client.h"

static void list_match_users(GtkWidget *widget, GdkEvent *event);
static void search_menu_click(GtkWidget *widget, GdkEventButton *event, GdkDisplay *display);
static void create_search_menu(GtkWidget *entry, GdkEvent *event);

void mx_configure_left_header(void) {
    GtkWidget *left_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), left_header, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(left_header), 8);
    gtk_widget_set_size_request(GTK_WIDGET(left_header), L_FIELD_WIDTH, 23);
        
    entry_search = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(entry_search), "entry");
    gtk_box_pack_start(GTK_BOX(left_header), entry_search, TRUE, TRUE, 0);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_search), text_for_labels[13]);
    gtk_entry_set_max_length(GTK_ENTRY(entry_search), 20);
    gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    g_signal_connect(G_OBJECT(entry_search), "changed", G_CALLBACK(list_match_users), NULL);
}

static void list_match_users(GtkWidget *widget, GdkEvent *event) {
    int len = mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget)));
    if (len == 0) {
        mx_destroy_popups();
        return;
    }
    create_search_menu(widget, event);
}



// Click on the window to close the menu
static void search_menu_click(GtkWidget *widget, GdkEventButton *event, GdkDisplay *display) {
    if (search_menu != NULL) {
        GtkAllocation alloc;
        gtk_widget_get_allocation(GTK_WIDGET(search_menu), &alloc);
        gint x_search, y_search;
        gtk_window_get_position(GTK_WINDOW(search_menu), &x_search, &y_search);
        selected_msg_widget = NULL;
        if (event->x_root > x_search + alloc.width || event->y_root > y_search +alloc.height
            || event->x_root < x_search || event->y_root < y_search) {    
            mx_destroy_popups();
        }
    }
}

static void create_search_menu(GtkWidget *entry, GdkEvent *event) {
    mx_destroy_popups();

    // Create window and grab focus of the mouse
    //==================================================================================
    search_menu = gtk_window_new(GTK_WINDOW_POPUP);
    gtk_widget_set_device_events(GTK_WIDGET(search_menu), gtk_get_current_event_device(), GDK_ALL_EVENTS_MASK);
    gtk_widget_realize(GTK_WIDGET(search_menu));
    gtk_window_set_resizable(GTK_WINDOW(search_menu), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(search_menu), FALSE);

    gdk_window_show(gtk_widget_get_window(GTK_WIDGET(search_menu)));
    GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(chat_area));
    GdkCursor *cursor = gdk_cursor_new_from_name (display, "default");
    GdkGrabStatus status = gdk_seat_grab(gdk_display_get_default_seat(display),
        gtk_widget_get_window(GTK_WIDGET(window)), GDK_SEAT_CAPABILITY_ALL_POINTING, TRUE,
        cursor, event, NULL, NULL);
    g_object_unref(G_OBJECT(cursor));    
    g_signal_connect(G_OBJECT(window), "button_press_event",
        G_CALLBACK(search_menu_click), display);
    //==================================================================================

    // Fill the search window
    //==================================================================================
    GtkWidget *search_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(search_menu), search_container);
    gtk_widget_set_name(GTK_WIDGET(search_container), "tools_menu");

    //==================================================================================

    // Move window of tools to the mouse click position
    GtkAllocation alloc;
    gtk_widget_get_allocation(GTK_WIDGET(entry), &alloc);

    gint x_win;
    gint y_win;
    gtk_window_get_position(GTK_WINDOW(window), &x_win, &y_win);

    gtk_window_move(GTK_WINDOW(search_menu), x_win + alloc.x, y_win + 77);

    gtk_widget_show_all(GTK_WIDGET(search_menu));
}
