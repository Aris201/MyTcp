#ifndef __NETWORKING_COMMON__
#define __NETWORKING_COMMON__

#include <stdint.h>
#include <stdio.h>

typedef uint16_t port_t;

typedef struct _buffer {
	size_t		length;
	uint8_t*	buffer;
} buffer_t;

typedef buffer_t host_t;

typedef struct _endpoint
{
	host_t		host;
	port_t		port;
} endpoint_t;

typedef struct _connection
{
	endpoint_t	target_endpoint;
	endpoint_t	src_endpoint;
} connection_t;

#endif