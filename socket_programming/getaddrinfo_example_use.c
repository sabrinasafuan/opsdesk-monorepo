/******************************************************************
 *
 *  showip.c -- Shows the IP addresses for a host given on the
 *              command line
 *  Usage - showip <hostname>
 *
 *  Goal : To use getaddrinfo() to extract required information
 *         to show the IP address of a host
 *
 *  "getaddrinfo gives a result to a linked list of the node/hostname"
 *  int getaddrinfo(const char *restrict nodename, // nodename == hostname
 *                  const char *restrict servname, // servname == port
 *                  const struct addrinfo *restrict hints,
 *                  struct addrinfo **restrict res); // store result in res
 *
 *  void freeaddrinfo(struct addrinfo *ai);
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // size_t
#include <sys/socket.h> // sockaddr struct
#include <netdb.h>      // addrinfo struct
#include <arpa/inet.h>  // in_addr struct and htonl, htons, ntohl, ntohs
#include <netinet/in.h> // in_addr struct, sockaddr_in struct, sockaddr_in6 struct

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *res; // store result of server info
    struct addrinfo *p;
    int status; // fd the file descriptor

    // allocated space to struct and make sure it is empty "0"
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC; // AF_UNSPEC indicates that getaddrinfo() should return socket addresses for any address family (either IPv4 or IPv6
    hints.ai_flags = AI_PASSIVE; // wildcard, fill my IP for me...

    // use port 3490 for utp/udp
    if (status == getaddrinfo(NULL, "3490", &hints, &res) != 0) // returns 0 if succeed
    {
        fprintf(stderr, "gai/getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    else
    {
        fprintf(stdout, "Successfully called getaddrinfo!\n");
    }

    freeaddrinfo(res); // free
}