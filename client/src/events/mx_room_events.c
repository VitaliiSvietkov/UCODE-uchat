#include "../../inc/uchat_client.h"

void room_click(GtkWidget *widget, GdkEventButton *event, gpointer id) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        unsigned int uid = (unsigned int)(uintptr_t)id;

        char *err_msg = 0;
        int status = sqlite3_open("client/data/messages.db", &messages_db);
        if (status != SQLITE_OK) {
            mx_write_to_log("Can`t open database.\n", 2);
            sqlite3_close(messages_db);
            messages_db = NULL; 
            return;
        }
        sqlite3_exec(messages_db,
                    "CREATE TABLE IF NOT EXISTS Messages(id UNSIGNED INT, uid UNSIGNED INT, Text TEXT, Image BLOB);",
                    0, 0, &err_msg);

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

        gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(chat_area));
    }
}


// Close a room on the Esc button press
void room_close(GtkWidget *widget, GdkEventKey *event) {
    switch (event->keyval) {
        case GDK_KEY_Escape:
            if (blackout != NULL) {
                gtk_widget_destroy(GTK_WIDGET(blackout));
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
                blackout = NULL;

                gtk_widget_set_can_focus(GTK_WIDGET(chat_area), TRUE);
                gtk_widget_grab_focus(GTK_WIDGET(chat_area));
                break;
            }
            mx_destroy_popups();
            if (message_enter_area != NULL) {
                gtk_widget_destroy(GTK_WIDGET(message_enter_area));
                message_enter_area = NULL;
                gtk_widget_destroy(GTK_WIDGET(right_container));
                right_container = NULL;
                sqlite3_close(messages_db);
                messages_db = NULL;
            }
            if (curr_room_msg_head != NULL)
                mx_clear_message_list(&curr_room_msg_head);
            break;
        default:
            break;
    }
}
