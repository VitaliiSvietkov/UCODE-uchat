#include "../inc/uchat_client.h"

static void pop_up_destroy(GtkWidget *widget, gpointer revealer) {
    gtk_widget_destroy(GTK_WIDGET(widget));
    //g_object_unref(G_OBJECT(revealer)); ???????????
}

void mx_run_error_pop_up(const char *text) {
    GtkWidget *revealer = gtk_revealer_new();
    gtk_revealer_set_transition_type(GTK_REVEALER(revealer), 
        GTK_REVEALER_TRANSITION_TYPE_CROSSFADE);
    gtk_revealer_set_transition_duration(GTK_REVEALER(revealer), 1000);
    
    GtkWidget *body = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(revealer), body);
    g_signal_connect(G_OBJECT(body), "button_press_event",
        G_CALLBACK(pop_up_destroy), (gpointer)revealer);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(box), "pop_up_error");
    gtk_container_add(GTK_CONTAINER(body), box);

    GtkWidget *label = gtk_label_new(text);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    int width = mx_strlen(text) * 5;
    width += 30;
    gtk_fixed_put(GTK_FIXED(chat_area), revealer, 
        CUR_WIDTH - width - 20, 20);

    gtk_widget_show_all(GTK_WIDGET(revealer));
    gtk_revealer_set_reveal_child(GTK_REVEALER(revealer), TRUE);
}
