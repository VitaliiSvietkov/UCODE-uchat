#include "../inc/uchat_client.h"

int main(int argc, char *argv[]) {
    //sqlite3* DB;
    //const char *DBdir = "../data/test.db";

    mx_init_global_vars();
    mx_write_language_data_from_bd();
    mx_get_language_arr();
    
    mx_database_init();
    mx_write_user_data_from_bd();
    mx_init_user();
  
    gtk_init(&argc, &argv);

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/css/uchat.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    mx_load_images();
  
    // Create a new window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    mx_init_window();
    // Create a main area where all widgets will be shown
    mx_configure_main_area();
    // Create a selection area
    mx_configure_content_selection_area();

    // Create a chat list area
    chats_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), chats_list, 0, 105);
    gtk_box_pack_start(GTK_BOX(chats_list), mx_create_room(0), FALSE, FALSE, 0);
    active_leftbar_container = NULL;

    // Create a contacts list area
    contacts_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(chat_area), contacts_list, 0, 95);

    // Create a settings menu
    mx_configure_settings_menu_area();

    gtk_widget_show_all (window);
    // Hide unneccessary widgets
    gtk_widget_hide(GTK_WIDGET(chats_list));
    gtk_widget_hide(GTK_WIDGET(contacts_list));
    gtk_widget_hide(GTK_WIDGET(settings_menu));

    printf("%d\n", t_user.id);

    gtk_main();

    g_object_unref(G_OBJECT(t_user.avatar));
    free(t_user.FirstName);
    free(t_user.SecondName);
    free(t_user.pseudonim);
    free(t_user.description);
    mx_del_strarr(&text_for_labels);
    while (labels_head != NULL)
        mx_label_pop_front(&labels_head);
    return 0;
}
