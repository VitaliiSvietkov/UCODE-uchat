#include "../../inc/uchat_client.h"

t_chats_list *mx_push_back_chat(t_chats_list **head, int uid, GdkPixbuf *image, GtkWidget *widget) {
    if (*head == NULL) {
        *head = mx_new_chat_node(uid, image, widget);
        return *head;
    }
    else {
        t_chats_list *curr_node = *head;
        while (curr_node->next != NULL)
            curr_node = curr_node->next;
        curr_node->next = mx_new_chat_node(uid, image, widget);
        return curr_node->next;
    }
}
