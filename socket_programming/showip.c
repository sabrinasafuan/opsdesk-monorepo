/******************************************************************
 *
 *  Purpose : showip is a program that uses getaddrinfo() to print
 *            the IP addresses for the host specified
 *
 *  EXAMPLE : ./showip www.google.com
 *  OUTPUT : Successfully retrieved serverinfo !
 *  IP addresses for www.google.com:
 *
 *  IPv4: 172.217.27.4
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
 *      "inet_ntop converts binary (network) address representation to printable string"
 *  3.  const char *inet_ntop(int ai_family, const void *restrict src, char dst[restrict size], socklen_t size);
 *  4.  void freeaddrinfo(struct addrinfo *ai);
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // size_t
#include <sys/socket.h> // sockaddr struct
#include <netdb.h>      // addrinfo struct
#include <arpa/inet.h>  // in_addr struct and htonl, htons, ntohl, ntohs
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p; // used to iterate results of servinfo

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = AF_UNSPEC; // use either IPv4 / IPv6
    hints.ai_family = AF_INET;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: ./showip <hostname> \n");
        return 1;
    }

    if (status == getaddrinfo(argv[1], NULL, &hints, &servinfo) != 0)
    {
        fprintf(stderr, "gai error unable to retrieve getaddrinfo() err code %s\n", gai_strerror(status));
        return 2;
    }
    else
    {
        fprintf(stdout, "Successfully retrieved serverinfo !\n");
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    // once obtained link list of server info, iterate...
    // to get the IP addressess
    for (p = servinfo; p != NULL; p->ai_next)
    {
        void *addr;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;
        char *ipver;

        // if IPv4
        if (p->ai_family == AF_INET)
        {
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr); // assign address of ipv4->sin_addr to addr
            ipver = "IPv4";
        }
        else if (p->ai_family == AF_INET6)
        {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert IP to str using inet_ntop (ie. network to printable/presentable) and print
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf(" %s: %s\n", ipver, ipstr);

        freeaddrinfo(servinfo);
        return 0;
    }
}