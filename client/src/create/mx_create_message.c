#include "../../inc/uchat_client.h"

static void draw_image(GtkWidget *widget, cairo_t *cr, GdkPixbuf *data);

GtkWidget *mx_create_message(t_message *data) {
    GtkWidget *eventbox = gtk_event_box_new();
    if (data->uid == t_user.id)
        gtk_widget_set_name(GTK_WIDGET(eventbox), "usr_message");
    else
        gtk_widget_set_name(GTK_WIDGET(eventbox), "message");
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    if (data->image != NULL) {
        //GtkWidget *image = gtk_image_new_from_pixbuf(GDK_PIXBUF(data->image));
        GtkWidget *image = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(image), gdk_pixbuf_get_width(GDK_PIXBUF(data->image)), 
            gdk_pixbuf_get_height(GDK_PIXBUF(data->image)));
        g_signal_connect(G_OBJECT(image), "draw", G_CALLBACK(draw_image), data->image);
        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
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

    return eventbox;
}

static void draw_image(GtkWidget *widget, cairo_t *cr, GdkPixbuf *data) {
    int img_w, img_h;
    GtkAllocation alloc;
    gtk_widget_get_allocation(GTK_WIDGET(widget), &alloc);
    img_w = alloc.width;
    img_h = alloc.height;

    gdk_cairo_set_source_pixbuf(cr, data, 0, 0);

    double x = 0,
        y = 0,
        width = img_w,
        height = img_h,
        aspect = 1.0,                       /* aspect ratio */
        corner_radius = 12;         /* and corner curvature radius */
    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_fill(cr);
}
