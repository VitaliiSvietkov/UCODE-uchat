#include "../../inc/uchat_client.h"

GdkPixbuf *mx_size_image_down(GdkPixbuf *pixbuf) {
    int width = gdk_pixbuf_get_width(GDK_PIXBUF(pixbuf));
    int height = gdk_pixbuf_get_height(GDK_PIXBUF(pixbuf));

    if (width <= 500 && height <= 350)
        return pixbuf;
    else {
        int source_width = width;
        int source_height = height;
        if (width > height) {
            width = 500;
            height = (500 * source_height) / source_width;
            if (height > 350) {
                source_width = width;
                source_height = height;
                height = 350;
                width = (350 * source_width) / source_height;
            }
        }
        else {
            height = 350;
            width = (350 * source_width) / source_height;
            if (width > 500) {
                source_width = width;
                source_height = height;
                width = 500;
                height = (500 * source_height) / source_width;
            }
        }
    }

    GdkPixbuf *result = gdk_pixbuf_scale_simple(GDK_PIXBUF(pixbuf), 
        width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf);
    return result;
}
