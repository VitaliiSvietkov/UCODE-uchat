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
