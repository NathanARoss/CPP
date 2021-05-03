/*
Purpose:
	To help a theater keep track of available seats and total sales data.

Input:
	Price for each row in the theater
	Purchase option
	Row and column of the seat to purchase
	A confirmation from the user to purchase a seat
	Prompt to buy another seat
	Prompt to see advanced sales stats

Processing:
	Construct objects in memory
	Validate user input
		Make sure input can be successfully parsed
		Make sure input is in the right range
		Make sure supplied seat locations are valid, at the target price if supplied, and available
	Build a string representing availability of seats in the theater
		Represent all available seats
		Represent only seats with a given price
		Represent only the user selected seat
	Confirm seat purchase
		Accumulate total number of tickets sold
		Accumulate total ticket sales
		Keep track of which seats were sold
	Update theater map with recent purchases
	If the user wants to buy another ticket, loop back to purchase option prompt
	Display basic sales stats
	Prompt for the option to display more indept sales stats
		List of seats sold
		Seats available in each row
		Total seats available in theater
	Exit program

Output:
	Prompts for row prices
	Prompts for purchase options
	Prompts for target seat price
	Status of theater with parameters effecting how much information is displayed
	Input validation error messages
	Confirmation messages
	Basic sales stats
	Prompt for advanced sales stats
		List of seats sold
		available seats in each row
		total available seats in theater

Written by Nathan Ross, Kazou Higashi III, and Marc Flores
Last modified 3-24-16
*/

#include <vector> // std::vector
#include <string> // std::string
#include <iostream> //std::cin std::cout std::streamsize
#include <limits> // std::numeric_limits<T>::max()
#include <iomanip> // std::fixed std::showpoint std::setprecision
#include <ctype.h> // toupper()
#include <sstream> // std::stringstream

//ignore any remaining data in cin before the user pressed enter
void ignoreExtraInput()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//input a single character adnd ignore the rest
char inputChar()
{
	char input;
	std::cin.get(input);
	ignoreExtraInput();
	return input;
}

//input 1 object of basic typename type
//if the input cannot be parsed as the specified type by cin, return the supplied error value and fix cin
template <typename type>
type inputType(const type &errorValue)
{
	type input;
	std::cin >> input;
	if (std::cin.fail()) //detect failure to parse type
	{
		input = errorValue; //value returned when an type cannot be parsed
		std::cin.clear(); //remove error flag
	}
	ignoreExtraInput(); //remove any extra or invalid input
	return input;
}

class SeatPosition {
public:
	int rowSubscript, columnSubscript;
	SeatPosition(const int &_rowSubscript, const int &_columnSubscript) : rowSubscript(_rowSubscript), columnSubscript(_columnSubscript) {};

	std::string getDisplay() const
	{
		std::stringstream ss;
		ss << "Row " << rowSubscript + 1 << ", Column " << columnSubscript + 1;
		return ss.str();
	}
};

class Seat {
private:
	bool isVacant;

public:
	static const char EMPTY_SEAT = '*', FILLED_SEAT = '#';

	Seat(const bool &_isVacant) : isVacant(_isVacant) {};

	bool isAvailable() const
	{
		return isVacant;
	}

	char getDisplay() const
	{
		if (isVacant)
			return EMPTY_SEAT;
		else
			return FILLED_SEAT;
	}

	void setState(const bool &_isVacant)
	{
		isVacant = _isVacant;
	}
};

class Row {
private:
	const double price;
	std::vector<Seat> seats;

public:
	//initialize price and initialize all contained seats as available by default
	Row(const int &size, const double &_price) : price(_price) {
		seats.reserve(size);
		for (int i = 0; i < size; i++) {
			seats.push_back(Seat(true));
		}
	};

	//return a string containing characters representing each seat separated by a whitespace character
	std::string getDisplay() const
	{
		std::stringstream ss;
		for (const Seat &seat : seats)
			ss << ' ' << seat.getDisplay();
		return ss.str();
	}

	double getPrice() const
	{
		return price;
	}

	bool isSeatAvailable(const int &seatNumber) const
	{
		return seats[seatNumber].isAvailable();
	}

	//accesses an element of the Row object, necessary for drawing invidiual seats
	Seat getSeat(const int &seatNumber) const
	{
		return seats[seatNumber];
	}

	//returns the number of available seats in the given Row object
	int getAvailableSeatCount() const
	{
		int availableSeatCount = 0;
		for (const Seat &seat : seats)
			if (seat.isAvailable())
				++availableSeatCount;
		return availableSeatCount;
	}

	void setSeatAvailable(const int &seatNumber, const bool &availability)
	{
		seats[seatNumber].setState(availability);
	}
};

class Theater {
private:
	const int rowCount, columnCount;
	std::vector<Row> rows;

	//get a string representing the first 4 lines of the theater seating map
	//contains symbol legend and column labels
	static std::string getTheaterMapHeader(const int &seats)
	{
		std::stringstream ss;

		//legend
		ss << "   " << Seat::EMPTY_SEAT << " Available Seat\n";
		ss << "   " << Seat::FILLED_SEAT << " Reserved Seat\n";

		//10's place (0 digits are explicitly displayed as whitespace)
		ss << "  ";
		for (int i = 1; i <= seats; ++i)
		{
			char num = static_cast<char>('0' + i / 10);
			if (num == '0')
				num = ' ';
			ss << ' ' << num;
		}
		ss << '\n';

		//1's place
		ss << "  ";
		for (int i = 1; i <= seats; ++i)
			ss << ' ' << static_cast<char>('0' + i % 10);

		return ss.str();
	}

public:
	//the constructor gets the price of each row to pass to the Row's constructor
	Theater(const int &_rowCount, const int &_columnCount) : rowCount(_rowCount), columnCount(_columnCount) {
		double inputPrice;
		rows.reserve(rowCount);
		for (int i = 0; i < rowCount; i++) {
			std::cout << "What is the price of row " << (i + 1) << "? ";
			inputPrice = inputType<double>(-1.0);

			while (inputPrice < 0.0) {
				std::cout << "You have entered invalid input, please input a valid non-negative real number." << std::endl;
				inputPrice = inputType<double>(-1.0);
			}
			
			rows.push_back(Row(columnCount, inputPrice));
		}
	}

	//build a string representing all available seats
	std::string getDisplay() const
	{
		std::stringstream ss;
		ss << std::fixed << std::showpoint << std::setprecision(2);

		//display legend and seat number label at the top of the map
		std::cout << getTheaterMapHeader(columnCount) << '\n';

		for (size_t i = 0; i < rows.size(); ++i)
			ss << std::setw(2) << (i + 1) << rows[i].getDisplay() << " $" << rows[i].getPrice() << '\n';

		return ss.str();;
	}

	//build a string with all seats with of given price shown
	std::string getDisplay(const double &targetPrice) const
	{
		std::stringstream ss;
		ss << std::fixed << std::showpoint << std::setprecision(2);

		//display legend and seat number label at the top of the map
		std::cout << getTheaterMapHeader(columnCount) << '\n';

		for (size_t i = 0; i < rows.size(); ++i)
		{
			ss << std::setw(2) << (i + 1);

			//only print the state and price of a row if it is the targeted price
			if (abs(rows[i].getPrice() - targetPrice) < 0.01)
				ss << rows[i].getDisplay() << " $" << rows[i].getPrice();

			ss << '\n';
		}

		return ss.str();;
	}

	//build a string with the given seat shown and highlighted
	std::string getDisplay(const SeatPosition &targetPosition) const
	{
		std::stringstream ss;
		ss << std::fixed << std::showpoint << std::setprecision(2);

		//display legend and seat number label at the top of the map
		std::cout << getTheaterMapHeader(columnCount) << '\n';

		const int row = targetPosition.rowSubscript;
		const int seat = targetPosition.columnSubscript;
		std::string whiteSpace = std::string(seat * 2 + 1, ' ');
		std::string horizontalSelector = std::string(seat * 2 + 1, '-');

		for (int i = 0; i < row; ++i)
			ss << std::setw(2) << (i + 1) << whiteSpace << "|\n";
		
		ss << std::setw(2) << (row + 1) << std::string(seat * 2 + 1, '-')
			<< rows[row].getSeat(seat).getDisplay()
			<< std::string((columnCount - seat - 1) * 2, '-')
			<< " $" << rows[row].getPrice() << '\n';

		for (size_t i = row + 1; i < rows.size(); ++i)
			ss << std::setw(2) << (i + 1) << whiteSpace << "|\n";

		return ss.str();;
	}

	double getPrice(const SeatPosition &position) const
	{
		return rows[position.rowSubscript].getPrice();
	}

	//checks if the seat is outside the bounds of the theater
	bool isSeatExisting(const SeatPosition &position) const
	{
		return (position.rowSubscript < rowCount && position.rowSubscript >= 0 && position.columnSubscript < columnCount && position.columnSubscript >= 0);
	}

	bool isSeatAvailable(const SeatPosition &position) const
	{
		return rows[position.rowSubscript].isSeatAvailable(position.columnSubscript);
	}

	//return the number of available seats in a specific row
	int getSeatsAvailableInRow(const int &row) const
	{
		return rows[row].getAvailableSeatCount();
	}

	int getSeatsAvailableAtPrice(const double &targetPrice) const
	{
		int totalSeatsAvailable = 0;
		for (const Row &row : rows)
			if (abs(row.getPrice() - targetPrice) < 0.01)
				totalSeatsAvailable += row.getAvailableSeatCount();
		return totalSeatsAvailable;
	}

	//accumulate the number of available seats in each Row object
	int getTotalSeatsAvailable() const
	{
		int totalSeatsAvailable = 0;
		for (const Row &row : rows)
			totalSeatsAvailable += row.getAvailableSeatCount();
		return totalSeatsAvailable;
	}

	int getRowCount() const
	{
		return rowCount;
	}

	int getColumnCount() const
	{
		return columnCount;
	}

	//modify the seat at the given position to be available or unavailable
	//next time I do an assignment like this, it will be:
	//seats[position.rowSubscript][position.columnSubscript] = availability;
	void setSeatAvailable(const SeatPosition &position, const bool &availability)
	{
		rows[position.rowSubscript].setSeatAvailable(position.columnSubscript, availability);
	}
};

//prompt the user for a target seat price, reject prices with no available seats
double getTargetPrice(const Theater &theater)
{
	std::cout << "Enter your desired seat price: $";
	double targetPrice = inputType<double>(-1.0);

	while (targetPrice < 0.00 || theater.getSeatsAvailableAtPrice(targetPrice) == 0)
	{
		if (targetPrice < 0.00)
			std::cout << "Error. Enter a positive price: $";
		else
			std::cout << "Error, no seats available at that price. Enter a new price: $";

		targetPrice = inputType<double>(-1.0);
	}

	return targetPrice;
}

//prompt the user for the row and column of their desired seat
//re-enter seat position if seat does not exist, is not the target price, or is unavailable
SeatPosition getSelectedSeat(const Theater& theater, const double& targetPrice)
{
	std::cout << "Enter seat row: ";
	int rowSubscript = inputType<int>(-1) - 1;
	std::cout << "Enter seat number: ";
	int columnSubscript = inputType<int>(-1) - 1;
	SeatPosition selectedSeat(rowSubscript, columnSubscript);

	while (!theater.isSeatExisting(selectedSeat)
		|| (targetPrice >= 0.0 && theater.getPrice(selectedSeat) != targetPrice)
		|| !theater.isSeatAvailable(selectedSeat))
	{
		//error messages are arranged by priority of display
		//if a seat is not the target price, it does not matter if it is unavailable
		if (!theater.isSeatExisting(selectedSeat))
			std::cout << "Error. Seat does not exist.\n";
		else if (targetPrice >= 0.0 && theater.getPrice(selectedSeat) != targetPrice)
			std::cout << "Error. Seat is not target price.\n";
		else
			std::cout << "Error. Seat is unavailable.\n";

		std::cout << "Re-enter seat row: ";
		rowSubscript = inputType<int>(-1) - 1;
		std::cout << "Re-enter seat number: ";
		columnSubscript = inputType<int>(-1) - 1;
		selectedSeat = SeatPosition(rowSubscript, columnSubscript);
	}

	return selectedSeat;
}

//builds a string of seats sold this session, available seats in each row, and total available seats in theater
std::string getAdvancedStats(const Theater &theater, const std::vector<SeatPosition> &soldSeatsList)
{
	std::stringstream ss;

	ss << "List of seats sold this session:\n";
	for (const SeatPosition &seatPosition : soldSeatsList)
		ss << seatPosition.getDisplay() << '\n';
	ss << std::endl;

	ss << "List of available seats in each row" << std::endl;
	for (int rowSubscript = 0; rowSubscript < theater.getRowCount(); ++rowSubscript)
		ss << "Row " << (rowSubscript + 1) << ": " << theater.getSeatsAvailableInRow(rowSubscript) << " seats\n";
	ss << std::endl;

	ss << "Total available seats in theater: " << theater.getTotalSeatsAvailable();

	return ss.str();
}

int main()
{
	const int THEATER_ROWS = 15;
	const int THEATER_COLUMNS = 30;

	//constructs all objects related to seating, asks user for row pricing
	Theater theater(THEATER_ROWS, THEATER_COLUMNS);
	std::cout << std::endl;

	//imagine that the session didn't always begin with an empty theater
	if (theater.getTotalSeatsAvailable() == 0)
		std::cout << "No seats available for purchase." << std::endl;
	else
	{
		//adjust formatting so double float prices display in US currency format
		std::cout << std::fixed << std::showpoint << std::setprecision(2);

		double totalSales = 0.00;
		int ticketsSold = 0;

		std::vector<SeatPosition> soldSeatsList;

		//if seats are available, sell them
		char buyAnother;
		do
		{
			//let the user see all available seating and the price of rows with available seating
			std::cout << theater.getDisplay();
			std::cout << std::endl;

			std::cout << "Option 1: Provide a target price to hide unwanted seating\n";
			std::cout << "Option 2: Continue to seat selection\n";
			std::cout << "Choice: ";
			char displayChoice = toupper(inputChar());

			//verify or re-enter choice input
			while (displayChoice < '1' || displayChoice > '2')
			{
				std::cout << "Error. Enter 1 or 2: ";
				displayChoice = toupper(inputChar());
			}

			std::cout << std::endl;

			//if the user chooses to hide unwanted seating
			double targetPrice = -1.00;
			if (displayChoice == '1')
			{
				//get the target seat price from the user, reject prices with no available seats
				targetPrice = getTargetPrice(theater);

				//only draw seats of the given price
				std::cout << theater.getDisplay(targetPrice) << std::endl;
			}

			//get the position of the desired seat, require that position be valid
			SeatPosition selectedSeat = getSelectedSeat(theater, targetPrice);

			std::cout << std::endl;

			//draw the theater again, this time with only the user's selected seat shown
			std::cout << theater.getDisplay(selectedSeat);

			std::cout << std::endl;

			//confirm the purchase because tickets are non-refundable
			std::cout << "This seat will cost $" << theater.getPrice(selectedSeat) << ". Confirm purchase? (Y/N): ";
			char confirmPurchase = toupper(inputChar());

			//this confirmation check if more strict than the "buy another" prompt, not saying no is not good enough
			if (confirmPurchase == 'Y')
			{
				++ticketsSold; //keep a count of ticket sales
				totalSales += theater.getPrice(selectedSeat); //keep a cash total of ticket sales
				theater.setSeatAvailable(selectedSeat, false); //mark the seat as sold
				soldSeatsList.push_back(selectedSeat); //record which seats were sold this session and in what order
			}

			//re-draw the theater to cover the seat selection screen regardless if a seat was sold or not
			std::cout << "\nTheater status\n";
			std::cout << std::endl;
			std::cout << theater.getDisplay() << std::endl;

			//offer to purchase another ticket only if there are seats available to be sold
			if (theater.getTotalSeatsAvailable() == 0)
			{
				std::cout << "No more seats available for purchase." << std::endl;
				buyAnother = 'N';
			}
			else
			{
				std::cout << "Buy another ticket? (Y/N): ";
				buyAnother = toupper(inputChar());
			}
		} while (buyAnother != 'N');

		//Basic session sale stats
		std::cout << std::endl;
		std::cout << "Sales stats for this session\n";
		std::cout << "Tickets sold: " << ticketsSold << std::endl;
		std::cout << "Total sales: $" << totalSales << std::endl;
		std::cout << std::endl;

		std::cout << "See advanced stats? (Y/N): ";
		char seeAdvancedStats = toupper(inputChar());

		//display advanced stats: list of the position of every seat sold this session, the number of available
		//seats in each row, and the total number of available seats in the theater
		if (seeAdvancedStats != 'N')
		{
			std::cout << std::endl;
			std::cout << getAdvancedStats(theater, soldSeatsList) << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
