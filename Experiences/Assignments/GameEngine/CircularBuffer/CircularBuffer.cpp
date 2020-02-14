#include "CircularBuffer.h"

CircularBuffer::CircularBuffer()
{
	// constructor
	// initialize m_size
	m_size = 0;
}

void CircularBuffer::pushBack(MyType& value)
{
	// initial
	if (m_size == 0)
	{
		m_tail = 0;
		m_head = 0;
		m_size = 1;
	}
	// before reaching Max Capacity
	else if (m_size >= 1 && m_size < BUFFER_CAPACITY)
	{
		// tail = oldest = no change
		m_head++;
		m_size++;

		if (m_head >= BUFFER_CAPACITY)
		{
			m_head -= BUFFER_CAPACITY;
		}

	}
	// when it is Max Capacity
	else if (m_size == BUFFER_CAPACITY)
	{
		m_head = m_tail;
		m_tail++;
		// m_size no change as it reaches max
		// check if tail is at max capacity slot, if so, m_tail will become 0, as 0th element is the oldest in the container
		if (m_tail >= BUFFER_CAPACITY)
		{
			m_tail = 0;
		}
	}

	// update the value with head index which is move to next element in above code
	m_buffer[m_head] = value;
}

void CircularBuffer::popBack()
{
	// check the array size
	if (m_size <= 0)
	{
		std::cout << "ERROR: Nothing in the array! " << std::endl;
	}
	else if (m_size == 1)
	{
		clear();
	}
	else
	{
		// move tail one step forward
		m_tail++;
		// if more than BUFFER_CAPACITY, minus BUFFER_CAPACITY
		if (m_tail >= BUFFER_CAPACITY)
		{
			m_tail -= BUFFER_CAPACITY;
		}
		// reduce m_size by 1
		m_size--;
	}
}

void CircularBuffer::popFront()
{
	// check the array size
	if (m_size <= 0)
	{
		std::cout << "ERROR: Nothing in the array! " << std::endl;
	}
	else if (m_size == 1)
	{
		clear();
	}
	else
	{
		// move head one step backward
		m_head--;
		// if more than BUFFER_CAPACITY, minus BUFFER_CAPACITY
		if (m_head < 0)
		{
			m_head += BUFFER_CAPACITY;
		}
		// reduce m_size by 1
		m_size--;
	}
}

void CircularBuffer::clear()
{
	// clear out tail and head then set size back to 0
	m_tail = 0;
	m_head = 0;
	m_size = 0;
}

MyType& CircularBuffer::getAt(int index)
{
	// check if input index is out of range
	// A : index bigger and equal to capacity, index starts with 0
	// B : index is negative
	// C : index is bigger than current capacity size
	if (index >= BUFFER_CAPACITY || index < 0 || index >= m_size)
	{
		std::cout << "ERROR: Input index is out of array size!" << std::endl;
		return index;
	}

	// index starts from head all the way back to tail
	// check head and tail and re-adjust the value to get the correct index
	int temp = m_head - index;
	// if head - index < 0, temp += Max, so it will not be negative value
	if (temp < 0)
	{
		temp += BUFFER_CAPACITY;
	}

	// return value based on index
	return m_buffer[temp];
}

int CircularBuffer::getSize() const
{
	// return current element size
	return m_size;
}

void CircularBuffer::display()
{
	if (m_size > 0)
	{
		for (int i = 0; i != BUFFER_CAPACITY; i++)
		{
			std::cout << "  |  " << m_buffer[i] << "  |  ";
		}

		std::cout << std::endl << std::endl;
		std::cout << "	Head-> Value: " << m_buffer[m_head] << " -------- " << "Index: " << m_head << std::endl;
		std::cout << "	Tail-> Value: " << m_buffer[m_tail] << " -------- " << "Index: " << m_tail << std::endl;
		std::cout << "	Current container size: " << m_size << std::endl;
	}

	std::cout << std::endl << std::endl << std::endl;
}
