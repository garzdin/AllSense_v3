/*
 * buffer.cpp
 *
 * Created: 3/11/2018 2:25:21 PM
 *  Author: Teodor
 */ 

#include <avr/interrupt.h>
#include "buffer.h"

Buffer::Buffer(size_t size) {
	this->size_ = size;
	this->buf_ = (uint8_t *) malloc(sizeof(uint8_t) * size);
}

Buffer::~Buffer() {
	free(this->buf_);
}

void Buffer::reset(void)
{
	this->head_ = this->tail_;
}

bool Buffer::empty(void)
{
	//if head and tail are equal, we are empty
	return this->head_ == this->tail_;
}

bool Buffer::full(void)
{
	//If tail is ahead the head by 1, we are full
	return ((this->head_ + 1) % this->size_) == this->tail_;
}

uint8_t Buffer::size(void)
{	
	return this->size_ - 1;
}

void Buffer::put(uint8_t item)
{
	cli();
	
	this->buf_[this->head_] = item;
	this->head_ = (this->head_ + 1) % this->size_;

	if(this->head_ == this->tail_)
	{
		this->tail_ = (this->tail_ + 1) % this->size_;
	}
	
	sei();
}

uint8_t Buffer::get(void)
{
	if(this->empty())
	{
		return 0;
	}
	
	cli();

	//Read data and advance the tail (we now have a free space)
	uint8_t val = this->buf_[this->tail_];
	this->tail_ = (this->tail_ + 1) % this->size_;

	sei();

	return val;
}