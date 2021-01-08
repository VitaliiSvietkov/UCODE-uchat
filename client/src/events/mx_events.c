#include "../../inc/uchat_client.h"

void image_click(GtkWidget *widget, GdkEventButton *event, t_img_button *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (!(data->active)) {
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED, FALSE);
            data->active = true;
        }
        else {
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_CHECKED);
            data->active = false;
        }
    }
}
void activate_prelight(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_CHECKED))
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}
void deactivate_prelight(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_CHECKED))
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

// Blackout
//==============================================================
void blackout_destroy(GtkWidget *widget, GdkEventButton *event, GtkWidget *box) {
    if ( (event->type == GDK_BUTTON_PRESS && event->button == 1) ) {
        GtkAllocation alloc;
        gtk_widget_get_allocation(GTK_WIDGET(box), &alloc);
        if ( (event->x < alloc.x || event->x > (alloc.x + alloc.width))
            || (event->y < alloc.y || event->y > (alloc.y + alloc.height)) ) {
            gtk_widget_destroy(GTK_WIDGET(blackout));
            blackout = NULL;

            if (NewFirstName != NULL) {
                free(NewFirstName);
                NewFirstName = NULL;
                free(NewPseudonim);
                NewPseudonim = NULL;
                free(NewDescription);
                NewDescription = NULL;
                g_object_unref(G_OBJECT(NewAvatar));
                NewAvatar = NULL;
            }
            if (NewSecondName != NULL) {
                free(NewSecondName);
                NewSecondName = NULL;
            }
        }

        gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    }
}
//==============================================================

// Close image
//========================================================
void close_image_click_event(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (NewFirstName != NULL) {
            free(NewFirstName);
            NewFirstName = NULL;
            free(NewPseudonim);
            NewPseudonim = NULL;
            free(NewDescription);
            NewDescription = NULL;
            g_object_unref(G_OBJECT(NewAvatar));
        }
        if (NewSecondName != NULL)
            free(NewSecondName);
        NewSecondName = NULL;
        gtk_widget_destroy(GTK_WIDGET(blackout));
        blackout = NULL;

        gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    }
}
//========================================================
