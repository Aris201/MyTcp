#ifndef __TCP_CONNECTION_HANDLER_MODULE_INTERNAL__
#define __TCP_CONNECTION_HANDLER_MODULE_INTERNAL__

#include <winsock2.h>

#include "node_list.h"
#include "tcp_connection_handler_module.h"
#include "networking_common.h"

typedef struct _connection_window {
	size_t						window_size;
	uint8_t*					window_buffer;
	uint8_t*					read_position;
	uint8_t*					write_position;
} connection_window_t;

typedef struct _tcp_outgoing_connection {
	connection_t				handled_connection;
	connection_window_t			connection_window;
} tcp_outgoing_connection_t;

typedef struct tcp_incomming_connection {
	connection_t				handled_connection;
} tcp_incomming_connection_t;

typedef struct _tcp_connection_handler 
{
	SOCKET						socket;
	node_t*						all_incomming_connections_list;
	node_t*						all_outgoing_connections_list;
} tcp_connection_handler_t;


static tcp_connection_handler_status_t create_raw_socket(SOCKET* raw_socket);


#endif