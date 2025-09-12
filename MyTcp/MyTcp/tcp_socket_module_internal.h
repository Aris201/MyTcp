#ifndef __TCP_SOCKET_MODULE_INTERNAL__
#define __TCP_SOCKET_MODULE_INTERNAL__

#include "networking_common.h"

typedef struct _tcp_socket {
	endpoint_t	socket_endpoint;
	port_t		source_port;
} tcp_socket_t;

#endif