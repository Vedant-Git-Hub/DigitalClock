#ifndef H_COMMON_H_
#define H_COMMON_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_RING_BUFF_SIZE		256


typedef struct{
	uint8_t *buff;
	uint8_t buff_length;
	volatile uint16_t write_ind;
	volatile uint16_t read_ind;
}RING_BUFFER_T;


RING_BUFFER_T *ringbuffer_init(uint8_t *, uint8_t );
bool rignbuffer_push(RING_BUFFER_T *, uint8_t *, uint8_t );
uint8_t ringbuffer_pop();
bool ringbuffer_isFull();
bool ringbuffer_isEmpty();
void ringbuffer_deinit(RING_BUFFER_T *);

#endif
