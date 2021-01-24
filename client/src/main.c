#include "../inc/uchat_client.h"

int main(int argc, char *argv[]) {
    /*if (argc != 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("ERROR opening socket");
    }
    
    server = gethostbyname(argv[1]);
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
    }*/



    mx_init_global_vars();
    mx_get_language_arr();
    
    mx_database_init();
    //mx_write_user_data_from_bd();
    mx_init_user();
    gtk_init(&argc, &argv);

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/css/standard/uchat.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  
    // Create a new window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    mx_init_window();

    // Create a main area where all widgets will be shown
    mx_configure_main_area();

    gtk_widget_show_all (window);
    mx_create_registration_menu();

    gtk_main();
    mx_free_data();

    /*char sendBuffer[1025];
    bzero(sendBuffer, 1025);
    sprintf(sendBuffer, "Exit");
    if (send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0) {
         perror("ERROR writing to socket");
    }

    close(sockfd);*/
    return 0;
}
