/******************************************************************
 *
 *  Purpose : This is a program that gives a simple example on how to
 *            use bind after successful connection to endpoint with socket
 *
 *            Once we have a socket we may associate the socket to a port
 *            on our local machine (it is done if we are going to listen()
 *            for incoming connections on a specific port).
 *
 *  Function calls used :
 *
 *  1.  "getaddrinfo gives a result to a linked list of the node/hostname"
 *      int getaddrinfo(const char *restrict nodename, // nodename == hostname
 *                  const char *restrict servname, // servname == port
 *                  const struct addrinfo *restrict hints,
 *                  struct addrinfo **restrict res); // store result in res
 *  2.  const char *gai_strerror(int errcode);
 *
 *     "domain is your PF_INET/PF_INET6, type : SOCK_STREAM/SOCK_DGRAM, protocol : 0
 *      or other protocol depending on the type TCP/UDP"
 *
 *     "These args tells what kind of socket we'd like IPv4/IPv6, stream or datagram
 *     "TCP/UDP"
 *  3. int socket(int domain, int type, int protocol);
 *  4. int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
 *  5. void freeaddrinfo(struct addrinfo *ai);
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // size_t
#include <sys/socket.h> // sockaddr struct, socket()
#include <netdb.h>      // addrinfo struct
#include <arpa/inet.h>  // in_addr struct and htonl, htons, ntohl, ntohs
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int status;
    struct addrinfo hints;
    struct addrinfo *res; // server info results (linked list)

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // help fill in my IP for me, using AI_PASSIVE we are telling the program
                                 // to bind to the IP of the host it's running on
    hints.ai_protocol = 0;

    // use tcp
    if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0)
    {
        fprintf(stderr, "gai error unable to get address info %s\n", gai_strerror(status));
        return 1;
    }
    else
    {
        fprintf(stdout, "successfully retrieved address info \n");
    }

    int sockfd;

    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
    {
        fprintf(stderr, "Error unable to create connection endpoint\n");
        return 2;
    }
    else
    {
        printf("Successfully created communication endpoint\n");
    }

    if (socket > 0)
    {
        int bind_status;
        if ((bind_status = bind(sockfd, res->ai_addr, res->ai_addrlen)) < 0)
        {
            fprintf(stderr, "Error binding...\n");
        }
        else
        {
            printf("Binding is successful...\n");
        }
    }

    freeaddrinfo(res);
    return 0;
}