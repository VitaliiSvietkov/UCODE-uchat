#include "../inc/uchat_client.h"

// Change avatar button
//============================================================================================
void change_avatart_btn_click(GtkWidget *widget, GdkEvent *event) {
    if (widget) {}
    if (event) {}
    printf("BUTTON PRESSED\n");
}
//============================================================================================

// Edit username field
//============================================================================================
void return_image_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_widget_show_all(GTK_WIDGET(edit_user_main_screen));
    }
    if (widget) {}
}

void edit_username_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_username_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_username_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_username_icon), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT);
}

void edit_eventbox_click_event(GtkWidget *widget, GdkEventButton *event,
    GtkWidget *data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_hide(GTK_WIDGET(edit_user_main_screen));
        gtk_widget_show_all(GTK_WIDGET(data));
    }
    if (widget) {}
}
//============================================================================================

// Edit pseudonim field
//============================================================================================
void edit_pseudo_eventbox_enter_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_widget_set_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void edit_pseudo_eventbox_leave_notify_event(GtkWidget *widget, GdkEvent *event,
    GtkWidget *data) {
    if (event) {}
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(edit_pseudo_icon), GTK_STATE_FLAG_PRELIGHT);
    gtk_widget_unset_state_flags(GTK_WIDGET(data), GTK_STATE_FLAG_PRELIGHT);
}
//============================================================================================

// Change description field
//============================================================================================
void change_description_entry_change_event(GtkWidget *widget) {
    if (widget) {}
    printf("HDS\n");
}
//============================================================================================
