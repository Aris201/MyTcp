#ifndef __CONNECTION_MODULE__
#define __CONNECTION_MODULE__

#include "window_module.h"
#include "networking_common.h"

typedef uint32_t seq_t;
typedef uint32_t ack_t;

typedef enum _connection_status {
	CONNECTION_MODULE_INVALID_VALUE = -1,
	CONNECTION_MODULE_SUCCESS = 0,
} connection_status_t;

typedef enum _connection_state {
	SYN_SENT,
	SYN_RECEIVED,
	ESTABLISHED,
	FIN_SENT,
	FIN_RECEIVED,
	CLOSING,
	CLOSED
} connection_state_t;

typedef struct _connections_endpoints {
	endpoint_t					src_endpoint;
	endpoint_t					dst_endpoint;
} connection_endpoints_t;

typedef struct _connection {
	connection_endpoints_t		sendpoints;
	connection_state_t			state;
	seq_t						seq;
	ack_t						ack;
	window_t*					window;
};



#endif // !__CONNECTION_MODULE__

