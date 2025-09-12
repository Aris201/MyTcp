#ifndef __TCP_CONNECTION_HANDLER_MODULE__
#define __TCP_CONNECTION_HANDLER_MODULE__

#define MY_TCP_PROTOCOL_ID (123)

typedef enum _tcp_connection_handler_status
{
	INVALID_VALUE = -1,
	SUCCESS = 0,
	MALLOC_FAILED,
	CREATE_SOCKET_FAILED,
	SET_SOCKET_OPT_FAILED,
	INVALID_ARGUMENTS,
} tcp_connection_handler_status_t;

typedef struct _tcp_connection_handler tcp_connection_handler_t;

tcp_connection_handler_status_t create_tcp_connection_handler(tcp_connection_handler_t** tcp_connection_handler_ptr);

void close_tcp_connection_handler(tcp_connection_handler_t** tcp_connection_handler_ptr);
#endif

