#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT "8080"   // port we're listening on
#define BACKLOG 10 

int main() {
    int status, sockey,new_fd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints;
    struct addrinfo *serverinfo;

    // address info
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IPV4 or IPV6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // bind to localhost
    if ((status = getaddrinfo(NULL, PORT, &hints, &serverinfo)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }
    // socket (this should be a loop)
    sockey = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    // Bind to a port
    bind(sockey, serverinfo->ai_addr, serverinfo->ai_addrlen);
    // free the addrinfo
    freeaddrinfo(serverinfo);
    // listen on that port
    listen(sockey, BACKLOG);

    printf("server listening on port %s\n", PORT);
    // accept
    // Will be like reading a file
    // Need a while loop in here for listening
    while (1) {
        addr_size = sizeof their_addr;
        new_fd = accept(sockey, (struct sockaddr*)&their_addr, &addr_size);
        // accept is failed if -1
        if (new_fd >= 0) {
            // do something
            printf("received a thing");
            char *msg = "Beej was here!";
            int len, bytes_sent;
            len = strlen(msg);
            bytes_sent = send(new_fd, msg, len, 0);
            close(new_fd);
        }
    }


    return 0;
}