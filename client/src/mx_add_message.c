#include "../inc/uchat_client.h"

void mx_add_message(GtkWidget *container, t_message *message) {
    GtkWidget *msg = mx_create_message(message);
    GtkWidget *day_show = NULL;


    if (message->id == 1) {
        char *day_info = mx_strndup(ctime(&message->seconds) + 4, 7);
        day_info = mx_strjoin(day_info, ctime(&message->seconds) + 20);
        GtkWidget *first_date = gtk_label_new(day_info);
        free(day_info);
        gtk_widget_set_name(GTK_WIDGET(first_date), "day_info_show");
        gtk_widget_set_halign(GTK_WIDGET(first_date), GTK_ALIGN_CENTER);
        gtk_widget_set_margin_top(GTK_WIDGET(first_date), 5);
        gtk_box_pack_start(GTK_BOX(container), first_date, FALSE, FALSE, 0);
    }
    if (message->next != NULL && message->next->seconds - message->seconds >= 86400) {
        char *day_info = mx_strndup(ctime(&message->next->seconds) + 4, 7);
        day_info = mx_strjoin(day_info, ctime(&message->next->seconds) + 20);
        day_show = gtk_label_new(day_info);
        free(day_info);
        gtk_widget_set_name(GTK_WIDGET(day_show), "day_info_show");
        gtk_widget_set_halign(GTK_WIDGET(day_show), GTK_ALIGN_CENTER);
        gtk_widget_set_margin_top(GTK_WIDGET(day_show), 5); 
    }

    if (message->uid == (unsigned int)t_user.id) {
        gtk_widget_set_halign(GTK_WIDGET(msg), GTK_ALIGN_END);
        gtk_widget_set_margin_end(GTK_WIDGET(msg), 7);
    }
    else {
        gtk_widget_set_halign(GTK_WIDGET(msg), GTK_ALIGN_START);
        gtk_widget_set_margin_start(GTK_WIDGET(msg), 5);
    }

    gtk_widget_set_margin_top(GTK_WIDGET(msg), 5);

    gtk_box_pack_start(GTK_BOX(container), msg, FALSE, FALSE, 0); 

    if (message->next != NULL && message->next->seconds - message->seconds >= 86400
        && day_show != NULL)
        gtk_box_pack_start(GTK_BOX(container), day_show, FALSE, FALSE, 0);

    gtk_widget_show_all(GTK_WIDGET(msg));
}
