/******************************************************************
 *
 *  Purpose : This is a program that gives a simple example on how to
 *            use socket
 *
 *  Usage : ./socket_example_use www.github.com
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
 *  4. void freeaddrinfo(struct addrinfo *ai);
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
    if (argc < 2)
    {
        printf("Usage : ./socket_example_use <hostname> \n");
    }

    char *hostname;
    char *servername;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0; // Specifying 0 in this field indicates that socket addresses with any protocol can be returned by getaddrinfo()

    if ((status = getaddrinfo(argv[1], "80", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "gai error unable to get server info %s\n", gai_strerror(status));
        return 1;
    }

    int sockfd; // file descriptor for socket()

    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0)
    {
        fprintf(stderr, "Unable to create communication endpoint... ");
        return 2;
    }
    else
    {
        printf("successfully created communication endpoint! \n");
    }

    freeaddrinfo(servinfo);

    return 0;
}