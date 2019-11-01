#include <stdlib.h>
#include <iostream>
#include <windows.h>

class UIntPacker
{
private:
	unsigned int m_data;
	unsigned int m_bitCount; //to count how many bits are used.

public:

	UIntPacker()
	{
		m_bitCount = 0;
	}

	//pack the "value" into m_data, it retuns true if there are enough bits available 
	//bitCount : the bit count of "value"
	bool pack(unsigned int value, unsigned int bitCount)
	{
		if (m_bitCount + bitCount <= 32)
		{
			m_bitCount += bitCount;

			// shift the binary to left
			m_data = m_data << bitCount;
			// use OR gate to add in  data
			m_data = m_data | value;
		}
		else
		{
			std::cout << "Failed to pack!! More than 32 bitCount \n " << std::endl;
			return false;
		}
		
	}

	unsigned int extract(unsigned int bitCount)
	{
		unsigned int temp = 1;

		temp = (temp << bitCount) - 1;
		temp = temp & m_data;
		m_data = m_data >> bitCount;

		return temp;
	}
};

// ================================================================================================================================================ =

// the purpose of this class is to test your understanding of bit operations 
// it's less common we need to split the int into smaller data type, but there are few cases you will need to do this
// for exp, you are sending(or storing) byte arrays(byte stream), in order to store the date type larger than byte, you will
// need to split it
class UIntSplitter
{
public:
	unsigned char m_bytes[4];

	//store "1 unsigned int" value into "4 unsigned char"
	void storeUInt(unsigned int value)
	{
		for (int i = 0; i < 4; ++i)
		{
			unsigned int temp = 1;
			temp = (temp << 8) - 1;
			m_bytes[i] = value & temp;
			value = value >> 8;
		}
	}

	//merge the bytes(unsigned char) and return the unsigned int value
	unsigned int getInt(void)
	{
		unsigned int temp = 0;
		for (int i = 3; i >= 0; --i)
		{
			// shift the binary to left
			temp = temp << 8;
			// use OR gate to add in  data
			temp = temp | m_bytes[i];
		}

		return temp;
	}

};

//example of using class UIntPacker
int main()
{
	UIntPacker packer;

	int bit[4];

	// user key in data
	for (int i=0; i<4; ++i)
	{
		int value;
		std::cout << "Key in value: " << std::endl;
		std::cin >> value;
		std::cout << "Key in bit: " << std::endl;
		std::cin >> bit[i];

		packer.pack(value, bit[i]);
	}

	std::cout << std::endl;

	/*
	packer.pack(1, 1);
	packer.pack(14, 4);
	packer.pack(30, 5);
	packer.pack(2, 2);
	*/

	unsigned int value4T = packer.extract(bit[3]);
	unsigned int value3T = packer.extract(bit[2]);
	unsigned int value2T = packer.extract(bit[1]);
	unsigned int value1T = packer.extract(bit[0]);

	std::cout << value1T << std::endl;
	std::cout << value2T << std::endl;
	std::cout << value3T << std::endl;
	std::cout << value4T << std::endl;

	std::cout << std::endl;

	UIntSplitter splitter;

	int v;
	std::cout << "Store value in 4 char: " << std::endl;
	std::cin >> v;

	splitter.storeUInt(v);

	std::cout << splitter.getInt() << std::endl;

	system("PAUSE");

	return 0;
}
