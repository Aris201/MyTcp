#ifndef __WINDOW_MODULE_INTERNAL__
#define __WINDOW_MODULE_INTERNAL__

#include "window_module.h"
#include "networking_common.h"

typedef struct _window {
	buffer_t	window_buffer;
	uint32_t	read_position;
	uint32_t	write_position;
} window_t;


static void create_windows_buffer(buffer_t* window_buffer);

static void move_buffer_values_to_start(window_t* window_ptr);

#endif // !__WINDOW_MODULE_INTERNAL__
