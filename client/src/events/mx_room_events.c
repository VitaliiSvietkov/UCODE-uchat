#include "../../inc/uchat_client.h"

void room_click(GtkWidget *widget, GdkEventButton *event) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        if (message_enter_area != NULL) {
            gtk_widget_destroy(GTK_WIDGET(message_enter_area));
            message_enter_area = NULL;
        }
        if (right_container != NULL) {
            gtk_widget_destroy(GTK_WIDGET(right_container));
            right_container = NULL;
        }
        mx_create_messages_area();
        mx_create_message_enter_area();
    }
}

void room_close(GtkWidget *widget, GdkEventKey *event) {
    switch (event->keyval) {
        case GDK_KEY_Escape:
            if (blackout != NULL) {
                gtk_widget_destroy(GTK_WIDGET(blackout));
                if (NewFirstName != NULL) {
                    free(NewFirstName);
                    NewFirstName = NULL;
                }
                if (NewSecondName != NULL) {
                    free(NewSecondName);
                    NewSecondName = NULL;
                }
                if (NewPseudonim != NULL) {
                    free(NewPseudonim);
                    NewPseudonim = NULL;
                }
                if (NewDescription != NULL) {
                    free(NewDescription);
                    NewDescription = NULL;
                }
                if (NewAvatar != NULL) {
                    g_object_unref(G_OBJECT(NewAvatar));
                    NewAvatar = NULL;
                }
                blackout = NULL;
                break;
            }
            if (message_enter_area != NULL) {
                gtk_widget_destroy(GTK_WIDGET(message_enter_area));
                message_enter_area = NULL;
            }
            if (right_container != NULL) {
                gtk_widget_destroy(GTK_WIDGET(right_container));
                right_container = NULL;
            }
            break;
        default:
            break;
    }
}
