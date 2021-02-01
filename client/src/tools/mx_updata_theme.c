#include "../../inc/uchat_client.h"

void mx_update_theme(void) {
    /*
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    int st;
    char *errmsg;
    sprintf(sql, "SELECT THEME FROM USERS WHERE ID=%d;", t_user.id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    int theme = (int)sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sqlite3_close(db);
    switch (theme)
    {
    case 0:
    */
        g_object_unref(G_OBJECT(cssProvider));
        cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_path(cssProvider, "client/css/standard/uchat.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_widget_queue_draw(GTK_WIDGET(chat_area));
         /* 
        break;   
    case 1:
        g_object_unref(G_OBJECT(cssProvider));
        cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_path(cssProvider, "client/css/colored/uchat.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_widget_queue_draw(GTK_WIDGET(chat_area));
        break;
    default:
        break;
    }
    */
}
