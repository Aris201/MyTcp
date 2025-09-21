#include <stdlib.h>
#include <assert.h>

#include "window_module.h"
#include "window_module_internal.h"


window_status_t create_window(window_t** window_ptr) 
{
	window_status_t status = WINDOW_MODULE_INVALID_VALUE;
	window_t* window_tmp = NULL;

	if (NULL == window_ptr)
	{
		(void)printf("INVALID ARGUMENTS in create_window\n");
		status = WINDOW_MODULE_INVALID_ARGUMENTS;
		goto l_cleanup;
	}

	window_tmp = (window_t*)malloc(sizeof(window_t));
	if (NULL == window_tmp)
	{
		(void)printf("FAILED TO MALLOC the window tmp in create_window\n");
		status = WINDOW_MODULE_MALLOC_FAILED;
		goto l_cleanup;
	}

	create_windows_buffer(&window_tmp->window_buffer);

	window_tmp->read_position = 0;
	window_tmp->write_position = 0;

	*window_ptr = window_tmp;
	window_tmp = NULL;

	status = WINDOW_MODULE_SUCCESS;
	
l_cleanup:
	close_window(&window_tmp);
	return status;
}

window_status_t write_to_window(window_t* window_ptr, buffer_t* buffer_to_write)
{
	window_status_t status = WINDOW_MODULE_INVALID_VALUE;

	if (NULL == window_ptr || NULL == buffer_to_write)
	{
		(void)printf("INVALID ARGUMENTS in write_to_window\n");
		status = WINDOW_MODULE_INVALID_ARGUMENTS;
		goto l_cleanup;
	}

	if (window_ptr->write_position + buffer_to_write->length >= BUFFER_SIZE)
	{
		(void)printf("Not Enough Space in write_to_window\n");
		status = WINDOW_MODULE_NOT_ENOGUH_SPACE;
		goto l_cleanup;
	}

	for (uint32_t i = 0; buffer_to_write->length > i; ++i)
	{
		window_ptr->window_buffer.buffer[window_ptr->write_position + i] = buffer_to_write->buffer[i];
	}

	window_ptr->write_position += buffer_to_write->length;
	status = WINDOW_MODULE_SUCCESS;

l_cleanup:
	return status;
}

window_status_t read_from_window(window_t* window_ptr, buffer_t* buffer_to_read_into, uint32_t* bytes_read)
{
	window_status_t status = WINDOW_MODULE_INVALID_VALUE;
	uint32_t i = 0;

	if (NULL == window_ptr || NULL == buffer_to_read_into || NULL == bytes_read)
	{
		(void)printf("INVALID ARGUMENTS in read_from_window\n");
		status = WINDOW_MODULE_INVALID_ARGUMENTS;
		goto l_cleanup;
	}
	
	for (i = 0; buffer_to_read_into->length > i && window_ptr->write_position > i + window_ptr->read_position; ++i)
	{
		buffer_to_read_into->buffer[i] = window_ptr->window_buffer.buffer[window_ptr->read_position + i];
	}

	*bytes_read = i;
	window_ptr->read_position += i;

	move_buffer_values_to_start(window_ptr);

	status = WINDOW_MODULE_SUCCESS;

l_cleanup:
	return status;
}

window_status_t get_window_free_size(window_t* window_ptr, size_t* free_size)
{
	window_status_t status = WINDOW_MODULE_INVALID_VALUE;

	if (NULL == window_ptr || NULL == free_size)
	{
		(void)printf("INVALID ARGUMENTS in get_window_free_size\n");
		status = WINDOW_MODULE_INVALID_ARGUMENTS;
		goto l_cleanup;
	}

	*free_size = window_ptr->window_buffer.length - (size_t)window_ptr->write_position;
	status = WINDOW_MODULE_SUCCESS;

l_cleanup:
	return status;
}

void close_window(window_t** window_ptr)
{
	if (NULL != window_ptr && NULL != *window_ptr)
	{
		free((*window_ptr)->window_buffer.buffer);
		(*window_ptr)->window_buffer.buffer = NULL;

		free(*window_ptr);
		*window_ptr = NULL;
	}
}

static void create_windows_buffer(buffer_t* window_buffer)
{
	assert(NULL != window_buffer);
	
	window_buffer->length = BUFFER_SIZE;
	window_buffer->buffer = (uint8_t*)malloc(BUFFER_SIZE);

	assert(NULL != window_buffer->buffer);
}

static void move_buffer_values_to_start(window_t* window_ptr)
{
	uint32_t i = 0;

	assert(NULL != window_ptr);

	for (i = 0; window_ptr->write_position - window_ptr->read_position > i; ++i)
	{
		window_ptr->window_buffer.buffer[i] = window_ptr->window_buffer.buffer[i + window_ptr->read_position];
	}

	window_ptr->write_position -= window_ptr->read_position;
	window_ptr->read_position = 0;
}