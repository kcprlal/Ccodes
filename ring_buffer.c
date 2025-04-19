/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"

bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize)
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);

	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0))
	{
		ringBuffer->buffer = dataBuffer;
		ringBuffer->size = dataBufferSize;
		ringBuffer->head = dataBuffer;
		ringBuffer->tail = dataBuffer;
		ringBuffer->isEmpty = true;
		ringBuffer->isFull = false;

		return true;
	}

	return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer)
	{
		ringBuffer->head = ringBuffer->buffer;
		ringBuffer->tail = ringBuffer->buffer;
		ringBuffer->isEmpty = true;
		ringBuffer->isFull = false;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	return ringBuffer->isEmpty;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer)
	{
		if (ringBuffer->isEmpty)
			return 0;
		else if (ringBuffer->isFull)
			return ringBuffer->size;
		else
		{
			if (ringBuffer->head >= ringBuffer->tail)
				return (ringBuffer->head - ringBuffer->tail);
			else
				return ringBuffer->size - (ringBuffer->tail - ringBuffer->head);
		}
	}
	return 0;
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer)
	{
		return ringBuffer->size;
	}
	return 0;
}

bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);

	if (ringBuffer)
	{
		if (ringBuffer->isFull)
		{
			return false;
		}

		*(ringBuffer->head) = c;
		ringBuffer->head++;

		if (ringBuffer->head >= ringBuffer->buffer + ringBuffer->size)
		{
			ringBuffer->head = ringBuffer->buffer;
		}

		ringBuffer->isEmpty = false;

		if (ringBuffer->head == ringBuffer->tail)
		{
			ringBuffer->isFull = true;
		}

		return true;
	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);

	if ((ringBuffer) && (c))
	{
		if (ringBuffer->isEmpty)
		{
			return false;
		}
		*c = *(ringBuffer->tail);
		ringBuffer->tail++;

		if (ringBuffer->tail >= ringBuffer->buffer + ringBuffer->size)
		{
			ringBuffer->tail = ringBuffer->buffer;
		}

		ringBuffer->isFull = false;

		if (ringBuffer->tail == ringBuffer->head)
		{
			ringBuffer->isEmpty = true;
		}
		return true;
	}
	return false;
}

