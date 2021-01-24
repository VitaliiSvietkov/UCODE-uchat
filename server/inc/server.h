#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h> 
#include "../libs/cjson/inc/cJSON.h"
#include <time.h>
#include <limits.h>
#include <signal.h>

#include <sqlite3.h>

#include "../../libraries/libmx/inc/libmx.h"


typedef struct socket_list {
	int sock_fd;
	bool is_logged;
	char *login;
	struct socket_list *next;
} connected_client_list_t;

typedef struct {
	fd_set read_descriptors;
	connected_client_list_t head;
} server_context_t;

void mx_check_port(int port);
int mx_listening_socket(int port);
void mx_error(char *msg, int status);
void mx_deamon(void);
int mx_socket_list_add(connected_client_list_t *head, int new_sock_fd);
connected_client_list_t *mx_socket_list_find(connected_client_list_t *head, int sock_fd);
int mx_socket_list_free(connected_client_list_t *head);
int mx_socket_list_remove(connected_client_list_t *head, int sock_fd);
void mx_write_to_log(char *msg, int stream);
struct timeval wait_time(int sec, int msec);

bool mx_check_user(char **data);

#endif
