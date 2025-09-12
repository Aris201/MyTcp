#include <assert.h>
#include <ws2tcpip.h>

#include "tcp_connection_handler_module.h"
#include "tcp_connection_handler_module_internal.h"

tcp_connection_handler_status_t create_tcp_connection_handler(tcp_connection_handler_t** tcp_connection_handler_ptr)
{
	tcp_connection_handler_status_t status = INVALID_VALUE;
	tcp_connection_handler_t* connection_handler_tmp = NULL;

	if (NULL == tcp_connection_handler_ptr)
	{
		(void)printf("Invalid Arguments tcp_connection_handler_ptr is null in create_tcp_connection_handler\n");
		status = INVALID_ARGUMENTS;
		goto l_cleanup;
	}

	connection_handler_tmp = (tcp_connection_handler_t*)malloc(sizeof(tcp_connection_handler_t));
	if (NULL == connection_handler_tmp)
	{
		(void)printf("Failed to malloc connection_handler_tmp in create_tcp_connection_handler\n");
		status = MALLOC_FAILED;
		goto l_cleanup;
	}

	status = create_raw_socket(connection_handler_tmp->socket);
	if (SUCCESS != status)
	{
		(void)printf("Failed to create raw socket in create_tcp_connection_handler\n");
		goto l_cleanup;
	}

	connection_handler_tmp->all_incomming_connections_list = NULL;
	connection_handler_tmp->all_outgoing_connections_list = NULL;

	*tcp_connection_handler_ptr = connection_handler_tmp;
	connection_handler_tmp = NULL;

	status = SUCCESS;

l_cleanup:
	free(connection_handler_tmp);
	return status;
}

void close_tcp_connection_handler(tcp_connection_handler_t** tcp_connection_handler_ptr)
{
	tcp_connection_handler_t* tmp_connection_handler = NULL;
	if (NULL != tcp_connection_handler_ptr)
	{
		tmp_connection_handler = *tcp_connection_handler_ptr;
		if (NULL != tmp_connection_handler)
		{
			(void)closesocket(tmp_connection_handler->socket);
			close_node_list(tmp_connection_handler->all_outgoing_connections_list)
		}
		free(*tcp_connection_handler_ptr);
		*tcp_connection_handler_ptr = NULL;
	}
}

static tcp_connection_handler_status_t create_raw_socket(SOCKET* raw_socket)
{
	tcp_connection_handler_status_t status = INVALID_VALUE;
	SOCKET socket_tmp = INVALID_SOCKET;

	assert(NULL != raw_socket);

	socket_tmp = socket(AF_INET, SOCK_RAW, MY_TCP_PROTOCOL_ID);
	if (INVALID_SOCKET == socket_tmp)
	{
		(void)printf("Failed to create socket in create_tcp_connection_handler with %d\n", WSAGetLastError());
		status = CREATE_SOCKET_FAILED;
		goto l_cleanup;
	}

	int opt = 1;
	if (SOCKET_ERROR == setsockopt(socket_tmp, IPPROTO_IP, IP_HDRINCL, (const char*)&opt, sizeof(opt))) {
		printf("setsockopt failed: %d\n", WSAGetLastError());
		status = SET_SOCKET_OPT_FAILED;
		goto l_cleanup;
	}

	*raw_socket = socket_tmp;
	socket_tmp == INVALID_SOCKET;

	status = SUCCESS;

l_cleanup:
	(void)closesocket(socket_tmp);
	return status;
}
