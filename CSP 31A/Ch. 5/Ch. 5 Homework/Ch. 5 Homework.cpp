/*
Purpose:
	Calculate the per floor and total occupancy rate of a hotel

Input:
	Number of floors
	Number of rooms on floor n
	Number of occupied rooms on floor n

Processing:
	Verify that number of floors >= 1
	Verify that number of rooms >= 10
	Verify that number of occuplied rooms >= 0
	Skip 13th floor

Output:
	Per floor occupancy rate
	Total number of rooms
	Total number of occupied rooms
	Total number of vacant rooms
	Total occupancy rate

Written by Nathan Ross
Last modified 2-27-16
*/

#include <iostream> // std::cout std::cin std::streamsize
#include <cstdlib> // EXIT_SUCCESS
#include <string> // std::string
#include <limits> // std::numeric_limits<T>::max()
#include <iomanip> // std::fixed std::setprecision(2) std::showpoint

// call after std::cin, forces one input per std::cin
void flushCin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(void)
{
	std::cout << rand() << std::endl;
	//all floating point values will be printed to at least 2 decimal places
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	// get the number of floors in the hotel
	int floorCount;
	std::cout << "Enter the number of floors: ";
	std::cin >> floorCount;
	flushCin();

	while (floorCount < 1)
	{
		std::cout << "Enter at least 1 floor: ";
		std::cin >> floorCount;
		flushCin();
	}

	std::cout << std::endl;

	// loop through all floors and accumulate the number of rooms and occupied rooms
	int roomCount = 0;
	int occupiedRoomCount = 0;

	for (int floor = 1; floor <= floorCount; ++floor)
	{
		// skip the 13th floor
		if (floor == 13)
			continue;

		// get number of rooms on floor
		int floorRoomCount;
		std::cout << "Enter the number of rooms on floor " << floor << ": ";
		std::cin >> floorRoomCount;
		flushCin();

		while (floorRoomCount < 10)
		{
			std::cout << "Enter at least 10 rooms: ";
			std::cin >> floorRoomCount;
			flushCin();
		}

		// get number of occupied rooms on floor
		int floorOccupiedRoomCount;
		std::cout << "Enter the number of occupied rooms on floor " << floor << ": ";
		std::cin >> floorOccupiedRoomCount;
		flushCin();

		while (floorOccupiedRoomCount < 0 || floorOccupiedRoomCount > floorRoomCount)
		{
			std::cout << "Enter the number of occupied rooms between 0 and " << floorRoomCount << ": ";
			std::cin >> floorOccupiedRoomCount;
			flushCin();
		}

		// display the current floor's occupancy rate
		std::cout << "The occupancy rate of floor " << floor << " is "
			<< static_cast<float>(floorOccupiedRoomCount) / static_cast<float>(floorRoomCount) << std::endl;

		//insert a blank line between floors
		std::cout << std::endl;

		// update room and occupied room accumulators
		roomCount += floorRoomCount;
		occupiedRoomCount += floorOccupiedRoomCount;
	}

	int vacantRoomCount = roomCount - occupiedRoomCount;

	std::cout << "The building has a total of " << roomCount << " rooms." << std::endl;
	std::cout << occupiedRoomCount << " of those rooms are occupied." << std::endl;
	std::cout << vacantRoomCount << " of those rooms are vacant." << std::endl;
	std::cout << "The building has a total occupancy rate of " << static_cast<float>(occupiedRoomCount) / static_cast<float>(roomCount) << std::endl;

	return EXIT_SUCCESS;
}