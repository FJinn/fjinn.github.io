#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdio.h>
#include <iostream>

#define BUFFER_CAPACITY 5

typedef int MyType;

class CircularBuffer
{
private:
	MyType m_buffer[BUFFER_CAPACITY];
	int m_size;
	int m_head;
	int m_tail;

public:
	CircularBuffer();

	void pushBack(MyType& value);
	// pop the oldest one (pop tail)
	void popBack(void);
	// pop the latest one (pop head)
	void popFront(void);
	void clear(void);

	MyType& getAt(int index); // index relative from front, example: front = index 0

	int getSize(void) const;

	// display the container for easy reading
	void display();
};

#endif
