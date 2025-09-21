#ifndef __WINDOW_MODULE__
#define __WINDOW_MODULE__

#include "networking_common.h"

#define BUFFER_SIZE (10000)

typedef enum _window_status {
	WINDOW_MODULE_INVALID_VALUE = -1,
	WINDOW_MODULE_SUCCESS = 0,
	WINDOW_MODULE_INVALID_ARGUMENTS,
	WINDOW_MODULE_MALLOC_FAILED,
	WINDOW_MODULE_NOT_ENOGUH_SPACE,
} window_status_t;

typedef struct _window window_t;


window_status_t create_window(window_t** window_ptr);

window_status_t write_to_window(window_t* window_ptr, buffer_t* buffer_to_write);

window_status_t read_from_window(window_t* window_ptr, buffer_t* buffer_to_read_into, uint32_t* bytes_read);

window_status_t get_window_free_size(window_t* window_ptr, size_t* free_size);

void close_window(window_t** window_ptr);

#endif // !__WINDOW_MODULE__
