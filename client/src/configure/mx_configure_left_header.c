#include "../../inc/uchat_client.h"

static void list_match_users(GtkWidget *widget, GdkEvent *event);
static void search_menu_click(GtkWidget *widget, GdkEventButton *event, 
    GdkDisplay *display);
static void create_search_menu(GtkWidget *entry, GdkEvent *event, 
    unsigned int *users_arr, int users_len);
static void fill_users_arr(unsigned int **arr, char **search_split, 
    char *pseudonim, int *len);
static void search_room_click(GtkWidget *widget, GdkEventButton *event, gpointer uid);

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
    g_signal_connect(G_OBJECT(entry_search), "changed", 
        G_CALLBACK(list_match_users), NULL);
}

static void list_match_users(GtkWidget *widget, GdkEvent *event) {
    int len = mx_strlen(gtk_entry_get_text(GTK_ENTRY(widget)));
    if (len == 0) {
        mx_destroy_popups();
        return;
    }
    char *search_text = mx_strdup(gtk_entry_get_text(GTK_ENTRY(widget)));
    char *search_pseudonim = NULL;
    char **search_split = mx_strsplit(search_text, ' ');
    if (search_split[0][0] == '@') {
        search_pseudonim = mx_strdup(search_text + 1);
        if (mx_strlen(search_pseudonim) == 0)
            search_pseudonim = mx_strjoin(search_pseudonim, "@");
    }
    free(search_text);
    if (search_pseudonim != NULL) {
        mx_del_strarr(&search_split);
        search_split = NULL;
    }

    unsigned int *users_arr = NULL;
    int users_len = 0;
    fill_users_arr(&users_arr, search_split, search_pseudonim, &users_len);
    if (search_pseudonim != NULL)
        free(search_pseudonim);
    if (search_split != NULL)
        mx_del_strarr(&search_split);

    create_search_menu(widget, event, users_arr, users_len);

    if (users_arr != NULL)
        free(users_arr);
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

static void create_search_menu(GtkWidget *entry, GdkEvent *event, 
    unsigned int *users_arr, int users_len) {

    // Create window and grab focus of the mouse
    //==================================================================================
    if (search_menu == NULL) {
        search_menu = gtk_window_new(GTK_WINDOW_POPUP);
        gtk_widget_set_device_events(GTK_WIDGET(search_menu), 
            gtk_get_current_event_device(), GDK_ALL_EVENTS_MASK);
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
    }
    //==================================================================================

    // Fill the search window
    //==================================================================================
    gtk_container_forall(GTK_CONTAINER(search_menu), (GtkCallback)gtk_widget_destroy, NULL);
    GtkAllocation win_alloc;
    GtkAllocation entry_alloc;
    gtk_widget_get_allocation(GTK_WIDGET(search_menu), &win_alloc);
    gtk_widget_get_allocation(GTK_WIDGET(entry), &entry_alloc);

    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, 
        win_alloc.height, 100, 100, win_alloc.height);
    GtkWidget *search_scroll_container = gtk_scrolled_window_new(NULL, vadjustment);
    gtk_widget_set_size_request(GTK_WIDGET(search_scroll_container), 
        entry_alloc.width, win_alloc.height);
    gtk_container_add(GTK_CONTAINER(search_menu), search_scroll_container);

    GtkWidget *search_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(search_scroll_container), search_container);
    gtk_widget_set_name(GTK_WIDGET(search_container), "search_menu");

    for (int i = 0; i < users_len; i++) {
        gtk_box_pack_start(GTK_BOX(search_container), 
            mx_create_room(users_arr[i], entry_alloc.width, search_room_click), FALSE, FALSE, 0);
    }

    //==================================================================================

    // Move window of tools to the mouse click position
    gint x_win;
    gint y_win;
    gtk_window_get_position(GTK_WINDOW(window), &x_win, &y_win);

    gtk_window_move(GTK_WINDOW(search_menu), x_win + entry_alloc.x, y_win + 77);
    gtk_widget_show_all(GTK_WIDGET(search_menu));
}

static void fill_users_arr(unsigned int **arr, char **search_split, char *pseudonim, int *len) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res = NULL;
    char sql[250];
    bzero(sql, 250);
    if (search_split != NULL)
        sprintf(sql, "SELECT ID FROM USERS\
                WHERE (INSTR(NAME, '%s') OR INSTR(SURENAME, '%s')) AND ID != %u;",
                search_split[0], search_split[1], (unsigned int)t_user.id);
    else
        sprintf(sql, "SELECT ID FROM USERS\
                WHERE INSTR(PSEUDONIM, '%s') != 0 AND ID != %u;", pseudonim, (unsigned int)t_user.id);

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    while (sqlite3_step(res) != SQLITE_DONE) {
        unsigned int uid = (unsigned int)sqlite3_column_int(res, 0);
        if (uid != (unsigned int)t_user.id && !mx_uint_arr_check_value(*arr, uid, *len))
            *len = mx_uint_array_insert(arr, uid, *len);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}

static void search_room_click(GtkWidget *widget, GdkEventButton *event, gpointer uid) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        sqlite3 *db = mx_opening_db();
        sqlite3_stmt *res = NULL;
        char sql[250];
        bzero(sql, 250);
        sprintf(sql, "SELECT ID FROM Messages\
                WHERE (addresser=%u OR destination=%u) AND (addresser=%u OR destination=%u);", 
                (unsigned int)(uintptr_t)uid, (unsigned int)t_user.id,
                (unsigned int)(uintptr_t)uid, (unsigned int)t_user.id);

        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (sqlite3_step(res) == SQLITE_DONE) {
            room_click(widget, event, uid);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return;
        }
        sqlite3_finalize(res);
        sqlite3_close(db);

        g_object_ref(G_OBJECT(widget));
        gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(GTK_WIDGET(widget))), GTK_WIDGET(widget));
        gtk_box_pack_start(GTK_BOX(chats_list), widget, FALSE, FALSE, 0);
        gtk_box_reorder_child(GTK_BOX(chats_list), widget, 0);
        g_signal_handlers_disconnect_by_func(G_OBJECT(widget), (gpointer)search_room_click, uid);
        g_signal_connect(G_OBJECT(widget), "button_press_event", 
            G_CALLBACK(room_click), uid);

        room_click(widget, event, uid);
    }
}
