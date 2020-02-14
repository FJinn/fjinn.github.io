#include <iostream>
#include <Windows.h>
#include <cmath>

class BitData
{
public:
	unsigned char m_data;

	BitData()
	{
		reset();
	}

	void reset()
	{
		m_data = 0;
	}

	void set(int location, bool flag) //location is started from '0'
	{
		if (location >= 0 && location <= 7) // 8 bits
		{
			if (flag == 1)
			{
				unsigned char tempNum = m_data; // store as a reference for retrieving and OR Gate later > Step 1

				m_data = m_data >> location; // shift right by location number > Step 2

				m_data = m_data | flag; // OR Gate to set the location bit as true(1) / false(0) > Step 3

				m_data = m_data << location; // shift left by location number to get initial position > Step 4

				m_data = m_data | tempNum; // use OR Gate to set previously (Step 2) missing bits back to 1 if they are 1 > Step 5
			}
			else if (flag == 0)
			{
				unsigned char tempNum = 1; // get bit of 1 > Step 1

				tempNum = tempNum << location; // shift left by location number > Step 2

				tempNum = ~tempNum; // reverse bit value > Step 3

				m_data = tempNum & m_data; // AND Gate to set the desired location (if true/1) to false (0) > Step 4
			}

		}
		else
		{
			std::cout << "More than 8 bits!!!" << std::endl;
		}
	}

	bool get(int location)
	{
		unsigned char tempNum = 1; // get bit of 1 > Step 1

		tempNum = tempNum << location; // shift left by location number > Step 2

		tempNum = m_data & tempNum; // AND Gate to get the bool of location bit > Step 3

		tempNum = tempNum >> location; // shift right by location number to get the bool > Step 4

		return tempNum;

	}
};


int main(void)
{
	BitData dat;
	dat.set(0, true);
	dat.set(1, false);
	dat.set(2, true);
	dat.set(3, true);
	//dat.set(3, false);

	for (int i = 0; i < 4; i++)
	{
		std::cout << (int)dat.get(i) << std::endl;
	}

	system("pause");



/*	bool value[8];
	value[0] = true;
	value[1] = true;
	value[2] = true;
	value[3] = true;
	value[4] = false;
	value[5] = true;
	value[6] = false;
	value[7] = true;

	unsigned char bitmaskData = 0;
	*/

	return 0;
}