#include "../../inc/uchat_client.h"

static void tools_click(GtkWidget *widget, GdkEventButton *event, GdkDisplay *display);
static void create_tools_menu(GdkEvent *event);
static void message_click(GtkWidget *widget, GdkEvent *event, t_message *data);
static void copy_click(GtkWidget *widget, t_message *data);
static void delete_click(GtkWidget *widget, t_message *data);

GtkWidget *mx_create_message(t_message *data) {
    GtkWidget *eventbox = gtk_event_box_new();

    char *msg_time = mx_strndup(ctime(&data->seconds) + 11, 5);
    GtkWidget *time_send = gtk_label_new(msg_time);
    gtk_widget_set_margin_bottom(GTK_WIDGET(time_send), 5);
    free(msg_time);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    if (data->uid == (unsigned int)t_user.id) {
        gtk_widget_set_name(GTK_WIDGET(eventbox), "usr_message");
        gtk_widget_set_halign(GTK_WIDGET(time_send), GTK_ALIGN_END);
    }
    else {
        gtk_widget_set_name(GTK_WIDGET(eventbox), "message");
        gtk_widget_set_halign(GTK_WIDGET(time_send), GTK_ALIGN_START);
        /* Display name of the addresser
        if (data->text != NULL) {
            GtkWidget *sender_name = gtk_label_new(NULL);

            sqlite3 *db = mx_opening_db();
            sqlite3_stmt *res = NULL;
            char sql[250];
            bzero(sql, 250);
            sprintf(sql, "SELECT NAME, SURENAME FROM USERS\
                    WHERE id=%u;", data->uid);
            sqlite3_prepare_v2(db, sql, -1, &res, 0);
            while (sqlite3_step(res) != SQLITE_DONE) {
                char *name = mx_strdup((char *)sqlite3_column_text(res, 0));
                gtk_label_set_text(GTK_LABEL(sender_name), name);
                free(name);
            }
            sqlite3_finalize(res);
            sqlite3_close(db);

            gtk_widget_set_name(GTK_WIDGET(sender_name), "sender_name");
            gtk_widget_set_halign(GTK_WIDGET(sender_name), GTK_ALIGN_START);
            gtk_widget_set_margin_top(GTK_WIDGET(sender_name), 5);
            gtk_widget_set_margin_start(GTK_WIDGET(sender_name), 10);
            gtk_box_pack_start(GTK_BOX(box), sender_name, FALSE, FALSE, 0);
        }*/
    }

    if (data->image != NULL) {
        GtkWidget *image = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(image), gdk_pixbuf_get_width(GDK_PIXBUF(data->image)), 
            gdk_pixbuf_get_height(GDK_PIXBUF(data->image)));
        g_signal_connect(G_OBJECT(image), "draw", G_CALLBACK(draw_image), data->image);
        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
        if (data->text == NULL)
            gtk_widget_set_name(GTK_WIDGET(eventbox), NULL);
    }
    if (data->text != NULL) {
        GtkWidget *label = gtk_label_new(data->text);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
        gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_START);
        gtk_widget_set_margin_top(GTK_WIDGET(label), 5);
        gtk_widget_set_margin_start(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_end(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_bottom(GTK_WIDGET(label), 5);
    }

    gtk_widget_set_margin_start(GTK_WIDGET(time_send), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(time_send), 10);
    gtk_box_pack_start(GTK_BOX(box), time_send, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(message_click), data);

    return eventbox;
}





// Click on the window to close the menu
static void tools_click(GtkWidget *widget, GdkEventButton *event, GdkDisplay *display) {
    if (tools_menu != NULL) {
        GtkAllocation alloc;
        gtk_widget_get_allocation(GTK_WIDGET(tools_menu), &alloc);
        gint x_tools, y_tools;
        gtk_window_get_position(GTK_WINDOW(tools_menu), &x_tools, &y_tools);
        selected_msg_widget = NULL;
        if (event->x_root > x_tools + alloc.width || event->y_root > y_tools +alloc.height
            || event->x_root < x_tools || event->y_root < y_tools) {    
            mx_destroy_popups();
        }
    }
}

static void create_tools_menu(GdkEvent *event) {
    mx_destroy_popups();

    tools_menu = gtk_window_new(GTK_WINDOW_POPUP);
    gtk_widget_set_device_events(GTK_WIDGET(tools_menu), gtk_get_current_event_device(), GDK_ALL_EVENTS_MASK);
    gtk_widget_realize(GTK_WIDGET(tools_menu));
    gtk_window_set_resizable(GTK_WINDOW(tools_menu), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(tools_menu), FALSE);

    gdk_window_show(gtk_widget_get_window(GTK_WIDGET(tools_menu)));
    GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(chat_area));
    GdkCursor *cursor = gdk_cursor_new_from_name (display, "default");
    GdkGrabStatus status = gdk_seat_grab(gdk_display_get_default_seat(display),
        gtk_widget_get_window(GTK_WIDGET(window)), GDK_SEAT_CAPABILITY_ALL_POINTING, TRUE,
        cursor, event, NULL, NULL);
    g_object_unref(G_OBJECT(cursor));    
    g_signal_connect(G_OBJECT(window), "button_press_event",
        G_CALLBACK(tools_click), display);
}

static void message_click(GtkWidget *widget, GdkEvent *event, t_message *data) {
    if (((GdkEventButton *)event)->type == GDK_BUTTON_PRESS 
        && ((GdkEventButton *)event)->button == 3) {
        selected_msg_widget = widget;

        create_tools_menu(event); // Creates the window of the tools menu (saves it to the 'tools_menu')
        GtkWidget *tools_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(tools_menu), tools_container);
        gtk_widget_set_name(GTK_WIDGET(tools_container), "tools_menu");

        GtkWidget *copy_btn = gtk_button_new_with_label(text_for_labels[35]);
        gtk_box_pack_start(GTK_BOX(tools_container), copy_btn, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(copy_btn), "tools_button");
        gtk_button_set_relief(GTK_BUTTON(copy_btn), GTK_RELIEF_NONE);
        gtk_widget_set_size_request(GTK_WIDGET(copy_btn), 150, 30);
        g_signal_connect(G_OBJECT(copy_btn), "clicked", G_CALLBACK(copy_click), data);

        GtkWidget *delete_btn = gtk_button_new_with_label(text_for_labels[36]);
        gtk_widget_set_name(GTK_WIDGET(delete_btn), "tools_button");
        gtk_button_set_relief(GTK_BUTTON(delete_btn), GTK_RELIEF_NONE);
        gtk_widget_set_size_request(GTK_WIDGET(delete_btn), 150, 30);
        gtk_box_pack_start(GTK_BOX(tools_container), delete_btn, FALSE, FALSE, 0);
        g_signal_connect(G_OBJECT(delete_btn), "clicked", G_CALLBACK(delete_click), data);

        // Move window of tools to the mouse click position
        gint x = ((GdkEventButton *)event)->x_root;
        gint y = ((GdkEventButton *)event)->y_root;
        gint x_win;
        gtk_window_get_position(GTK_WINDOW(window), &x_win, NULL);
        if (x + 150 >= x_win + CUR_WIDTH)
            x -= 150;
        gtk_window_move(GTK_WINDOW(tools_menu), x, y);

        gtk_widget_show_all(GTK_WIDGET(tools_menu));
    }
    else if (((GdkEventButton *)event)->type == GDK_BUTTON_PRESS)
        mx_destroy_popups();
}

static void copy_click(GtkWidget *widget, t_message *data) {
    if (data->text != NULL) {
        GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
        gtk_clipboard_clear(GTK_CLIPBOARD(clipboard));
        gtk_clipboard_set_text(GTK_CLIPBOARD(clipboard), data->text, mx_strlen(data->text));
    }

    mx_destroy_popups();
}

static void delete_click(GtkWidget *widget, t_message *data) {
    //gtk_widget_destroy(GTK_WIDGET(selected_msg_widget));
    selected_msg_widget = NULL;
    mx_remove_message(&curr_room_msg_head, data->id);

    gtk_container_forall(GTK_CONTAINER(t_chat_room_vars.messages_box), (GtkCallback)gtk_widget_destroy, NULL);
    t_message *msg = curr_room_msg_head;
    while (msg != NULL) {
        mx_add_message(t_chat_room_vars.messages_box, msg);
        msg = msg->next;
    }

    mx_destroy_popups();
}
