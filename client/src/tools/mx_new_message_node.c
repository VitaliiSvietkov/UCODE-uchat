#include "../../inc/uchat_client.h"

t_message *mx_new_message_node(char *text, unsigned int uid, 
    GdkPixbuf *image, time_t seconds) {
    t_message *node = (t_message *)malloc(sizeof(t_message));
    node->text = text;
    node->image = image;
    node->uid = uid;
    node->id = mx_message_list_size(&curr_room_msg_head) + 1;
    node->next = NULL;
    node->seconds = seconds;
    return node;
}
