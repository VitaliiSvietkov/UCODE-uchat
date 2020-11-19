#include "../inc/uchat_client.h"

void mx_do_drawing_background(cairo_t *cr) {
  struct winsize max;
  ioctl(0, TIOCGWINSZ, &max);

  cairo_set_source_rgba(cr, MX_E1E1E1, MX_E1E1E1, MX_E1E1E1, 1);
  cairo_rectangle(cr, CUR_WIDTH / 2, 0, CUR_WIDTH / 2, CUR_HEIGHT);
  cairo_fill(cr);

  cairo_set_source_rgba(cr, MX_1F1F1F, MX_1F1F1F, MX_1F1F1F, 1);
  cairo_rectangle(cr, 0, 0, CUR_WIDTH / 2, CUR_HEIGHT);
  cairo_fill(cr);
}

gboolean mx_on_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  mx_do_drawing_background(cr);
  if (user_data) {}
  if (widget) {}
  return FALSE;
}
