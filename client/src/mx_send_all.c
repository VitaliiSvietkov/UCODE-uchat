#include "../inc/uchat_client.h"

void mx_send_all(int *socket, void *buffer, size_t length) {
    if (*socket == -1){
        mx_connect_to_server(socket);
        //return 1;
    }
    unsigned char *ptr = (unsigned char *)buffer;
    while (length > 0) {
        usleep(70000);
        int i = send(*socket, ptr, length, 0);
        if(i == -1) {
            pthread_t thread_id;
            char *err_msg = "Connection lost\nTry again later";
            pthread_create(&thread_id, NULL, mx_run_error_pop_up, (void *)err_msg); 
            *socket = -1;
            return;
        }
        ptr += i;
        length -= i;
    }
}
