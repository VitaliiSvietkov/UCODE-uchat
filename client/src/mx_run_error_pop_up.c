#include "../inc/uchat_client.h"

static void pop_up_destroy(GtkWidget *widget) {
    gtk_widget_destroy(GTK_WIDGET(widget));
    gtk_widget_destroy(GTK_WIDGET(error_revealer));
}

void mx_run_error_pop_up(const char *text) {
    error_revealer = gtk_revealer_new();
    gtk_revealer_set_transition_type(GTK_REVEALER(error_revealer), 
        GTK_REVEALER_TRANSITION_TYPE_CROSSFADE);
    gtk_revealer_set_transition_duration(GTK_REVEALER(error_revealer), 1000);
    
    GtkWidget *body = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(error_revealer), body);
    g_signal_connect(G_OBJECT(body), "button_press_event",
        G_CALLBACK(pop_up_destroy), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(box), "pop_up_error");
    gtk_container_add(GTK_CONTAINER(body), box);

    GtkWidget *label = gtk_label_new(text);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    int width = mx_strlen(text) * 5;
    width += 30;
    gtk_fixed_put(GTK_FIXED(chat_area), error_revealer, 
        CUR_WIDTH - width - 20, 20);

    gtk_widget_show_all(GTK_WIDGET(error_revealer));
    gtk_revealer_set_reveal_child(GTK_REVEALER(error_revealer), TRUE);
}
