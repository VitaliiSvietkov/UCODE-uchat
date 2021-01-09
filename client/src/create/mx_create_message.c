#include "../../inc/uchat_client.h"

static void create_tools_menu(GdkEventButton *event);
static void message_click(GtkWidget *widget, GdkEventButton *event, t_message *data);

GtkWidget *mx_create_message(t_message *data) {
    GtkWidget *eventbox = gtk_event_box_new();
    if (data->uid == (unsigned int)t_user.id)
        gtk_widget_set_name(GTK_WIDGET(eventbox), "usr_message");
    else
        gtk_widget_set_name(GTK_WIDGET(eventbox), "message");
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

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
        gtk_widget_set_margin_top(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_start(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_end(GTK_WIDGET(label), 10);
        gtk_widget_set_margin_bottom(GTK_WIDGET(label), 10);
    }

    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(message_click), data);

    return eventbox;
}

static void create_tools_menu(GdkEventButton *event) {
    if (tools_menu != NULL) {
        gtk_widget_destroy(GTK_WIDGET(tools_menu));
        tools_menu = NULL;
    }
    if (more_box != NULL) {
        gtk_widget_destroy(GTK_WIDGET(more_box));
        more_box = NULL;
        more_image.active = false;
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_PRELIGHT);
        gtk_widget_unset_state_flags(GTK_WIDGET(more_image.box), GTK_STATE_FLAG_CHECKED);
    }

    tools_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(tools_menu), "tools_menu_1layer");

    GtkWidget *tools_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(tools_container), "tools_menu_2layer");
    gtk_box_pack_start(GTK_BOX(tools_menu), tools_container, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(chat_area), tools_menu, event->x + 340, event->y);

    gtk_widget_set_size_request(GTK_WIDGET(tools_container), 200, 200);

    gtk_widget_show_all(GTK_WIDGET(tools_menu));
}

static void message_click(GtkWidget *widget, GdkEventButton *event, t_message *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        create_tools_menu(event);
        //gtk_widget_destroy(GTK_WIDGET(widget));
        //mx_remove_message(&curr_room_msg_head, data->id);

        GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
        gtk_clipboard_clear(GTK_CLIPBOARD(clipboard));
        gtk_clipboard_set_text(GTK_CLIPBOARD(clipboard), data->text, mx_strlen(data->text));
    }
}
