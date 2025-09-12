#ifndef __NETWORKING_COMMON__
#define __NETWORKING_COMMON__

#include <stdint.h>
#include <stdio.h>

typedef uint16_t port_t;

typedef struct _host
{
	size_t		name_length;
	char*		hostname;
} host_t;

typedef struct _endpoint
{
	host_t		host;
	port_t		port;
} endpoint_t;

typedef struct _connection
{
	endpoint_t	endpoint;
	port_t		src_port;
} connection_t;
#endif