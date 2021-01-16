#include "../../inc/uchat_client.h"

GtkWidget *mx_create_room(unsigned int uid, gint width, void (*func)(GtkWidget *, GdkEventButton *, gpointer)) {
    GtkWidget *eventbox = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(eventbox), "eventbox_room");
    g_signal_connect(G_OBJECT(eventbox), "enter-notify-event",
        G_CALLBACK(activate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "leave-notify-event",
        G_CALLBACK(deactivate_prelight), NULL);
    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
        G_CALLBACK(*func), (gpointer)(uintptr_t)uid);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_margin_top(GTK_WIDGET(box), 5);
    gtk_widget_set_margin_bottom(GTK_WIDGET(box), 5);
    gtk_widget_set_size_request(GTK_WIDGET(box), width, 55);
    gtk_container_add(GTK_CONTAINER(eventbox), box);

    GtkWidget *avatar = NULL;
    GdkPixbuf *pixbuf = NULL;

    GtkWidget *title = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(title), "room_title");
    gtk_widget_set_margin_top(GTK_WIDGET(title), 5);
    GtkWidget *preview = gtk_label_new(NULL);
    gtk_widget_set_name(GTK_WIDGET(preview), "room_text_preview");
    gtk_widget_set_margin_top(GTK_WIDGET(preview), 10);

    if (uid == 0) {
        pixbuf = mx_get_pixbuf_with_size("client/img/standard/bookmark.png", 50, 50);
        gtk_label_set_text(GTK_LABEL(title), "Saved Messages");
        char *tmp_preview = "@";
        tmp_preview = mx_strjoin(tmp_preview, t_user.pseudonim);
        gtk_label_set_text(GTK_LABEL(preview), tmp_preview);
        free(tmp_preview);
        avatar = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
        gtk_widget_set_size_request(GTK_WIDGET(avatar), 50, 50);
        gtk_widget_set_margin_start(GTK_WIDGET(avatar), 15);
        g_object_unref(pixbuf);
    }
    else {
        // Load data from data base
        mx_read_photo_from_bd((int)uid);
        pixbuf = mx_get_pixbuf_with_size("client/img/avatar2.jpg", 50, 50);
        avatar = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixbuf));
        gtk_widget_set_size_request(GTK_WIDGET(avatar), 50, 50);
        gtk_widget_set_margin_start(GTK_WIDGET(avatar), 15);
        g_object_unref(pixbuf);

        sqlite3 *db = mx_opening_db();
        t_message *msg = NULL;
        sqlite3_stmt *res = NULL;
        char sql[250];
        bzero(sql, 250);
        sprintf(sql, "SELECT NAME, SURENAME FROM USERS\
                WHERE id=%u;", uid);
        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        while (sqlite3_step(res) != SQLITE_DONE) {
            char *name = mx_strdup((char *)sqlite3_column_text(res, 0));
            char *surname = mx_strdup((char *)sqlite3_column_text(res, 1));
            name = mx_strjoin(name, surname);
            gtk_label_set_text(GTK_LABEL(title), name);
            free(name);
            free(surname);
        }
        sqlite3_finalize(res);
        bzero(sql, 250);
        sprintf(sql, "SELECT PSEUDONIM FROM USERS WHERE id=%u;", uid);
        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        sqlite3_step(res);
        char *tmp_preview = mx_strdup((char *)sqlite3_column_text(res, 0));
        tmp_preview = mx_strjoin("@", tmp_preview);
        gtk_label_set_text(GTK_LABEL(preview), tmp_preview);
        free(tmp_preview);
        sqlite3_finalize(res);
        sqlite3_close(db);
    }
    gtk_box_pack_start(GTK_BOX(box), avatar, FALSE, FALSE, 0);
    
    GtkWidget *v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_start(GTK_WIDGET(v_box), 15);
    gtk_box_pack_start(GTK_BOX(box), v_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(v_box), title, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(v_box), preview, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(preview), GTK_ALIGN_START);

    return eventbox;
}
