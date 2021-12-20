/*
 * buffer.h
 *
 * Created: 3/11/2018 2:24:50 PM
 *  Author: Teodor
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#include <avr/io.h>
#include <stdlib.h>

class Buffer {
	public:
	Buffer(size_t size);
	~Buffer();
	
	void* operator new(size_t size) { return malloc(size); }
	void operator delete(void* ptr) { free(ptr); }

	void put(uint8_t item);
	uint8_t get(void);

	void reset(void);

	bool empty(void);
	bool full(void);
	uint8_t size(void);

	private:
	uint8_t * buf_;
	volatile size_t head_;
	volatile size_t tail_;
	size_t size_;
};


#endif /* BUFFER_H_ */