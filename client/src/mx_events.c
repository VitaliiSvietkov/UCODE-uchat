#include "../inc/uchat_client.h"

// Messages button
//=============================================================
void messages_enter_notify() {
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.hovered);
}

void messages_leave_notify() {
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.basic);
}

void messages_click(GtkWidget *widget, GdkEventButton *event) {
    if (messages_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &messages_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);

        gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = chats_list;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
    if (widget) {}
}
//=============================================================

// Contacts button
//=============================================================
void contacts_enter_notify() {
    if (!contacts_img.active)
        gtk_image_set_from_file(GTK_IMAGE(contacts_img.standard), contacts_img.hovered);
}

void contacts_leave_notify() {
    if (!contacts_img.active)
        gtk_image_set_from_file(GTK_IMAGE(contacts_img.standard), contacts_img.basic);
}

void contacts_click(GtkWidget *widget, GdkEventButton *event) {
    if (contacts_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &contacts_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
    }
    if (widget) {}
}
//=============================================================

// Settings button
//=============================================================
void settings_enter_notify() {
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.hovered);
}

void settings_leave_notify() {
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.basic);
}

void settings_click(GtkWidget *widget, GdkEventButton *event) {
    if (settings_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &settings_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);

        gtk_widget_hide(GTK_WIDGET(active_leftbar_container));
        active_leftbar_container = settings_menu;
        gtk_widget_show(GTK_WIDGET(active_leftbar_container));
    }
    if (widget) {}
}
//=============================================================

// Add button
//========================================================
void add_enter_notify() {
    if (!add_img.active)
        gtk_image_set_from_file(GTK_IMAGE(add_img.standard), add_img.hovered);
}

void add_leave_notify() {
    if (!add_img.active)
        gtk_image_set_from_file(GTK_IMAGE(add_img.standard), add_img.basic);
}
//========================================================

// Message entry field
//=================================================================================
void entry_chat_fill_event(GtkWidget *widget, GdkEvent *event) {
    int len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    if (len > 0) {
        gtk_widget_hide(GTK_WIDGET(t_img_event_box.ban_box));
        gtk_widget_show(GTK_WIDGET(t_img_event_box.tick_box));
    }
    else {
        gtk_widget_hide(GTK_WIDGET(t_img_event_box.tick_box));
        gtk_widget_show(GTK_WIDGET(t_img_event_box.ban_box));
    }
    if (event) {}
}
//=================================================================================

// Tick button
//=========================================================
void tick_enter_notify() {
    if (!tick_img.active)
        gtk_image_set_from_file(GTK_IMAGE(tick_img.standard), tick_img.hovered);
}

void tick_leave_notify() {
    if (!tick_img.active)
        gtk_image_set_from_file(GTK_IMAGE(tick_img.standard), tick_img.basic);
}
//========================================================

// More button
//=========================================================
void more_enter_notify() {
    if (!more_img.active)
        gtk_image_set_from_file(GTK_IMAGE(more_img.standard), more_img.hovered);
}

void more_leave_notify() {
    if (!more_img.active)
        gtk_image_set_from_file(GTK_IMAGE(more_img.standard), more_img.basic);
}
//=========================================================

// Edit_user icon in settings menu
//==================================
void edit_user_enter_notify() {
    if (!edit_user_img.active)
        gtk_image_set_from_file(GTK_IMAGE(edit_user_img.standard), edit_user_img.hovered);
}

void edit_user_leave_notify() {
    if (!edit_user_img.active)
        gtk_image_set_from_file(GTK_IMAGE(edit_user_img.standard), edit_user_img.basic);
}
//==================================

// Chat_settings icon in settings menu
//======================================
void chat_settings_enter_notify() {
    if (!chat_settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(chat_settings_img.standard), chat_settings_img.hovered);
}

void chat_settings_leave_notify() {
    if (!chat_settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(chat_settings_img.standard), chat_settings_img.basic);
}
//==================================

// Language icon in settings menu
//================================
void language_enter_notify() {
    if (!language_img.active)
        gtk_image_set_from_file(GTK_IMAGE(language_img.standard), language_img.hovered);
}

void language_leave_notify() {
    if (!language_img.active)
        gtk_image_set_from_file(GTK_IMAGE(language_img.standard), language_img.basic);
}
//=================================
