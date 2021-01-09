#include "../../inc/uchat_client.h"

t_message *mx_push_back_message(t_message **head, char *text, int uid, GdkPixbuf *image) {
    if (*head == NULL) {
        *head = mx_new_message_node(text, uid, image);
        return *head;
    }
    else {
        t_message *curr_node = *head;
        while (curr_node->next != NULL)
            curr_node = curr_node->next;
        curr_node->next = mx_new_message_node(text, uid, image);
        return curr_node->next;
    }
}