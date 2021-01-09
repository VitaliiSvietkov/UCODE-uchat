#include "../../inc/uchat_client.h"

unsigned int mx_remove_message(t_message **head, unsigned int id) {
    if (*head == NULL)
        return 0;
    if ((*head)->id == id) {
        t_message *temp = (*head)->next;
        mx_del_message_node(head);
        *head = temp;
        return id;
    }
    t_message *curr_node = *head;
    //t_message *next_node = curr_node->next;
    while (curr_node->next != NULL) {
        if (curr_node->next->id == id) {
            t_message *temp = curr_node->next->next;
            mx_del_message_node(&curr_node->next);
            curr_node->next = temp;
            return id;
        }
    }
    return 0;
}
