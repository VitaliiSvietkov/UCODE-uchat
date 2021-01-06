#include "../../inc/uchat_client.h"

void mx_del_message_node(t_message **data) {
    free((*data)->text);
    g_object_unref(G_OBJECT((*data)->image));
    free(*data);
    *data = NULL;
}
