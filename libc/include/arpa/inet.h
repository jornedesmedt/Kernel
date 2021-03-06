/**
    POSIX DESCRIPTION

    Name: arpa/inet.h -  definitions for internet operations
    Description: 
    
    

    The <arpa/inet.h> header shall define the in_port_t and in_addr_t types as described in <netinet/in.h>.

    The <arpa/inet.h> header shall define the in_addr structure as described in <netinet/in.h>.

    The <arpa/inet.h> header shall define the INET_ADDRSTRLEN [IP6] [Option Start]  and INET6_ADDRSTRLEN [Option End] macros as described in <netinet/in.h>.

    The following shall be declared as functions, or defined as macros, or both. If functions are declared, function prototypes shall be provided.

    uint32_t htonl(uint32_t);
    uint16_t htons(uint16_t);
    uint32_t ntohl(uint32_t);
    uint16_t ntohs(uint16_t);

    The <arpa/inet.h> header shall define the uint32_t and uint16_t types as described in <inttypes.h>.

    The following shall be declared as functions and may also be defined as macros. Function prototypes shall be provided.

    in_addr_t    inet_addr(const char *);
    char        *inet_ntoa(struct in_addr);
    const char  *inet_ntop(int, const void *restrict, char *restrict, socklen_t);
    int          inet_pton(int, const char *restrict, void *restrict);

    Inclusion of the <arpa/inet.h> header may also make visible all symbols from <netinet/in.h> and <inttypes.h>.

*/

#ifndef __POSIX_ARPA_INET_H__
#define __POSIX_ARPA_INET_H__

#include <netinet/in.h>
#include <inttypes.h>

uint32_t htonl(uint32_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint16_t ntohs(uint16_t);

#endif