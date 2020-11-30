#include "../inc/uchat_client.h"

gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Left area
    cairo_set_source_rgba(cr, MX_1F1F1F, MX_1F1F1F, MX_1F1F1F, 1);
    cairo_rectangle(cr, 0, 0, L_FIELD_WIDTH, CUR_HEIGHT);
    cairo_fill(cr);

    // Right area
    cairo_set_source_rgba(cr, MX_E1E1E1, MX_E1E1E1, MX_E1E1E1, 1);
    cairo_rectangle(cr, L_FIELD_WIDTH, 0, CUR_WIDTH - CUR_WIDTH / 3, CUR_HEIGHT);
    cairo_fill(cr);
    if (user_data) {}
    if (widget) {}
    return FALSE;
}

gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    cairo_set_source_rgba(cr, MX_1F1F1F, MX_1F1F1F, MX_1F1F1F, 1);
    cairo_rectangle(cr, 0, 0, CUR_WIDTH - CUR_WIDTH / 3, 50);
    cairo_fill(cr);
    if (widget) {}
    if (user_data) {}
    return FALSE;
}

gboolean mx_draw_event_delimiter(GtkWidget *widget, cairo_t *cr) {
    cairo_set_source_rgba(cr, MX_E1E1E1, MX_E1E1E1, MX_E1E1E1, 1);
    cairo_rectangle(cr, 0, 0, L_FIELD_WIDTH, 1);
    cairo_fill(cr);
    if (widget) {}
    return FALSE;
}

gboolean mx_draw_event_avatar(GtkWidget *widget, cairo_t *cr) {
    GdkPixbuf *pixbuf = mx_get_pixbuf_with_size("client/img/avatar.jpeg", 70, 70);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = 70,
        height = 70,
        aspect = 1.0,                       /* aspect ratio */
        corner_radius = height / 2.7;       /* and corner curvature radius */
    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_fill(cr);
    if (widget) {}
    return FALSE;
}

gboolean mx_draw_event_blackout(GtkWidget *widget, cairo_t *cr) {
    cairo_set_source_rgba(cr, MX_1F1F1F, MX_1F1F1F, MX_1F1F1F, 0.6);
    cairo_rectangle(cr, 0, 0, CUR_WIDTH, CUR_HEIGHT);
    cairo_fill(cr);
    if (widget) {}
    return FALSE;
}
