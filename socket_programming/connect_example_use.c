/******************************************************************
 *
 *  Purpose : This is a program that gives a simple example on how to
 *            use connect() after successful socket processing
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
 *  5. int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
 *  6. void freeaddrinfo(struct addrinfo *ai);
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
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "Usage: ./connect <hostname>");
        return 1;
    }

    int status;
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ((status = getaddrinfo(argv[1], "80", &hints, &res) != 0))
    {
        fprintf(stderr, "gai error %s \n", gai_strerror(status));
        return 2;
    }
    else
    {
        fprintf(stdout, "successfully retrieved address info \n");
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
    {
        perror("socket");
        // handle error, DO NOT continue
        // free res after connect..
    }
    else
    {
        printf("Successfully created communication endpoint\n");
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
    {
        perror("connect");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }
    else
    {
        printf("Connected ! \n");
    }

    freeaddrinfo(res);

    return 0;
}