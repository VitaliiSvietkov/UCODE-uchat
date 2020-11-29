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

gboolean mx_draw_event_delimiter(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    cairo_set_source_rgba(cr, MX_E1E1E1, MX_E1E1E1, MX_E1E1E1, 1);
    cairo_rectangle(cr, 0, 0, L_FIELD_WIDTH, 1);
    cairo_fill(cr);
    
    if (user_data) {}
    if (widget) {}
    return FALSE;
}
