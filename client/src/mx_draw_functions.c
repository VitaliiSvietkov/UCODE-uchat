#include "../inc/uchat_client.h"

gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Right area
    cairo_set_source_rgba(cr, MX_E1E1E1, MX_E1E1E1, MX_E1E1E1, 1);
    cairo_rectangle(cr, CUR_WIDTH / 3 + 50, 0, CUR_WIDTH - CUR_WIDTH / 3, CUR_HEIGHT);
    cairo_fill(cr);

    // Left area
    cairo_set_source_rgba(cr, MX_1F1F1F, MX_1F1F1F, MX_1F1F1F, 1);
    cairo_rectangle(cr, 0, 0, CUR_WIDTH / 3 + 50, CUR_HEIGHT);
    cairo_fill(cr);
    if (user_data) {}
    if (widget) {}
    return FALSE;
}

gboolean mx_draw_event_settings(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    cairo_set_source_surface(cr, t_settings.standard, 0, 0);
    cairo_paint(cr);
    if (widget) {}
    if (user_data) {}
    return FALSE;
}
