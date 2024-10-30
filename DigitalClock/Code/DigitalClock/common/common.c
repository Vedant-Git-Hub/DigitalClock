#include "common.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

RING_BUFFER_T *ringbuffer_init(uint8_t *buffer, uint8_t buff_size)
{
	if(buff_size < MAX_RING_BUFF_SIZE)
	{
		RING_BUFFER_T *ring_buff = (RING_BUFFER_T *)malloc(buff_size);
		if(ring_buff != NULL)
		{
			ring_buff->buff = buffer;
			ring_buff->buff_length = buff_size;
			ring_buff->write_ind = 0;
			ring_buff->read_ind = 0;
			return ring_buff;
		}
	}

	return NULL;
}

bool rignbuffer_push(RING_BUFFER_T *ring_buff, uint8_t *data, uint8_t bytes)
{
	if(bytes <= ring_buff->buff_length)
	{
		uint8_t data_ind = 0;
		while(!ringbuffer_isFull())
		{
			ring_buff->buff[ring_buff->write_ind++] = data[data_ind];
		}

		return true;
	}

	return false;
}

uint8_t ringbuffer_pop(RING_BUFFER_T *ring_buff, bool *read_stat)
{
	if(!ringbuffer_isEmpty())
	{
		*read_stat = true;
		return ring_buff->buff[ring_buff->read_ind++];
	}

	*read_stat = false;

	return 0;
}

bool ringbuffer_isFull()
{
	return false;
}

bool ringbuffer_isEmpty()
{
	return false;
}

void ringbuffer_deinit(RING_BUFFER_T *ring_buffer)
{
	free(ring_buffer);
}
