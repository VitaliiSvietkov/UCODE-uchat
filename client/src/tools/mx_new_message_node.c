#include "../../inc/uchat_client.h"

t_message *mx_new_message_node(char *text, int uid, GdkPixbuf *image) {
    t_message *node = (t_message *)malloc(sizeof(t_message));
    node->text = text;
    node->image = image;
    node->uid = uid;
    node->next = NULL;
    return node;
}
