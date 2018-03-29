#ifndef TRANSPORT_UDP_H
#define TRANSPORT_UDP_H

#if defined(LWIP_SOCKET)
#include <lwip/sockets.h>
#else
#include <netinet/in.h>
#endif /* LWIP_SOCKET */
#include "zhe-platform.h"

typedef struct zhe_address {
    struct sockaddr_in a;
} zhe_address_t;

#define TRANSPORT_MTU        1472u
#define TRANSPORT_MODE       TRANSPORT_PACKET
#define TRANSPORT_ADDRSTRLEN (4 + INET_ADDRSTRLEN + 6) /* udp/IP:PORT -- udp/ is 4, colon is 1, PORT in [1,5] */

zhe_time_t zhe_platform_time(void);
struct zhe_platform *zhe_platform_new(uint16_t port);
int zhe_platform_join(const struct zhe_platform *pf, const struct zhe_address *addr);
void zhe_platform_wait(const struct zhe_platform *pf);
int zhe_platform_recv(struct zhe_platform *pf, void * restrict buf, size_t size, zhe_address_t * restrict src);
void zhe_platform_background(struct zhe_platform * const platform);

#include <assert.h>
#define zhe_assert(x) assert(x)

#define PORT       0x1d17u   /* 7447 */
#define MCADDR     0xefff0001u /* 239.255.0.1 */

#if defined(__IAR_SYSTEMS_ICC__)
#define __ORDER_BIG_ENDIAN__ 4321
#define __ORDER_LITTLE_ENDIAN__ 1234
#if __LITTLE_ENDIAN__
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#else
#define __BYTE_ORDER__ __ORDER_BIG_ENDIAN__
#endif
#endif

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MCADDR_NBO MCADDR
#define PORT_NBO   PORT
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MCADDR_NBO ((uint32_t)(((MCADDR & 0xffu) << 24) | ((MCADDR & 0xff00u) << 8) | ((MCADDR & 0xff0000u) >> 8) | (MCADDR >> 24)))
#define PORT_NBO   ((uint16_t)(((PORT & 0xffu) << 8) | (PORT >> 8)))
#else
#error "byte order must be known for IP address constants"
#endif

static zhe_address_t scoutaddr = {
    .a = {
        .sin_family = AF_INET,
        .sin_port = PORT_NBO,
        .sin_addr = { .s_addr = MCADDR_NBO }
    }
};

#endif
