#include "../../inc/uchat_client.h"

GdkPixbuf *mx_size_image_down(GdkPixbuf *pixbuf) {
    int width = gdk_pixbuf_get_width(GDK_PIXBUF(pixbuf));
    int height = gdk_pixbuf_get_height(GDK_PIXBUF(pixbuf));

    if (width <= 500 && height <= 350)
        return pixbuf;

    while (width > 500 || height > 350) {
        width--;
        height--;
    }

    GdkPixbuf *result = gdk_pixbuf_scale_simple(GDK_PIXBUF(pixbuf), 
        width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf);
    return result;
}
