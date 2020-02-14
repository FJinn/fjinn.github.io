#include "CircularBuffer.h"

#define NOMINMAX
#include <Windows.h>

int main(void)
{
	CircularBuffer* circularContainer = new CircularBuffer();

	int choice = 0;

	do
	{
		std::cout << std::endl;
		circularContainer->display();

		std::cout << "Circular Buffer Menu" << std::endl;
		std::cout << "1. Input (Push back) new value to container." << std::endl;
		std::cout << "2. Remove (Pop back) oldest value from container." << std::endl;
		std::cout << "3. Remove (Pop front) latest value from container." << std::endl;
		std::cout << "4. Clear current container." << std::endl;
		std::cout << "5. Get the value at N index from latest to oldest." << std::endl;
		std::cout << "6. Get current container size." << std::endl;
		std::cout << "7. Exit." << std::endl;

		std::cout << std::endl << std::endl << std::endl << std::endl;

		switch (choice)
		{
		case 0:
			//executes loop if the input fails (e.g., no characters were read)
			while (std::cout << "Enter your choice: " && !(std::cin >> choice)) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "Invalid input! Please re-enter.\n";
			}

			break;
		case 1:

			system("CLS");
			int value;

			//executes loop if the input fails (e.g., no characters were read)
			while (std::cout << "Enter your value: " && !(std::cin >> value)) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "Invalid input! Please re-enter.\n";
			}

			circularContainer->pushBack(value);

			choice = 0;

			break;
		case 2:

			circularContainer->popBack();

			choice = 0;

			break;
		case 3:

			circularContainer->popFront();

			choice = 0;

			break;
		case 4:
			system("CLS");
			// clear container
			circularContainer->clear();
			
			choice = 0;

			break;
		case 5:
			system("CLS");
			// Get the value at N index from latest to oldest
			int index;

			//executes loop if the input fails (e.g., no characters were read)
			while (std::cout << "Enter the index: " && !(std::cin >> index)) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "Invalid input! Please re-enter.\n";
			}

			std::cout << std::endl;
			std::cout << "The value of input index: " << circularContainer->getAt(index) << std::endl;
			std::cout << std::endl;

			system("PAUSE");

			choice = 0;
			break;
		case 6:
			system("CLS");
			// Get current container size.
			std::cout << "The current container size: " << circularContainer->getSize() << std::endl;
			std::cout << std::endl;

			system("PAUSE");

			choice = 0;
			break;
		}
		system("CLS");
	} while (choice != 7);

	delete circularContainer;

	std::cout << std::endl;
	system("PAUSE");
	return 0;
}