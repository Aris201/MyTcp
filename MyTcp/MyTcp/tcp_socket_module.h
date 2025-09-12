#ifndef __TCP_SOCKET_MODULE__
#define __TCP_SOCKET_MODULE__

#include "networking_common.h"

typedef enum _tcp_socket_status
{
	INVALID_VALUE = -1,
	SUCCESS = 0,
} tcp_socket_status_t;

typedef struct _payload
{
	size_t		buffer_length;
	int8_t*		buffer;
} payload_t;

typedef struct _tcp_socket tcp_socket_t;

tcp_socket_status_t create_tcp_socket(tcp_socket_t** socket_ptr);

tcp_socket_status_t connect_tcp_socket(tcp_socket_t* socket_ptr, endpoint_t endpoint);

tcp_socket_status_t get_tcp_socket_endpoint(tcp_socket_t* socket_ptr, endpoint_t* endpoint);

tcp_socket_status_t write_data(tcp_socket_t* socket_ptr, 
							   payload_t* payload_to_send, 
							   size_t* written_amount);

tcp_socket_status_t read_data(tcp_socket_t* socket_ptr, 
							  payload_t* payload_to_read_into, 
							  size_t* read_amount);

tcp_socket_status_t dissconnect_tcp_socket(tcp_socket_t* socket_ptr);

tcp_socket_status_t close_tcp_socket(tcp_socket_t** socket_ptr);

#endif