/*
Purpose:
	A game of blackjack against an ai dealer following standard rules

	Player and dealer receive 2 cards at the start
	The dealer places one of their cards face up for the player to see
	The player can hit (receive additional cards) until they are satisfied with their score or go above 21 points
	When the player is finished, the dealer shows their cards and hits while following conditions exist:
		The dealer's hand's score is fewer than 17 points
		or the score is 17 and 11 of the points come from an ace
	The player with the hgihest score wins with the following exceptions:
		If a player or dealer's score goes above 21 points, they bust (lose)
		If both the player and dealer bust, then the game is a tie
		A 21 point hand with only 2 cards (blackjack) beats a 21 point hand with more than 2 cards

Input:
	Take another card?
	Play again?

Processing:
	Generating random cards to draw
	Determining the score of a hand
	Determining who won

Output:
	Welcome message
	Dealer's first card
	Cards in player's hand at each step
	Best score of player's hand at each step
	Final cards and score of dealer's and player's hand
	Whether the user won, lost, or tied
	Prompt to play agin

Written by Nathan Ross
Last modified 3-13-16
*/

#include <iostream> // std::cout std::cin std::streamsize
#include <limits> // std::numeric_limits<T>::max()
#include <cstdlib> // rand() EXIT_SUCCESS
#include <time.h> // std::time() time_t
#include <vector> // std::vector<T>
#include <string> // std::string
#include <sstream> // std::stringstream

class Card
{
private:
	unsigned char data;

public:
	enum Types
	{
		Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
	};

	//empty constructor
	Card() : data(0) {}

	//value constructor
	Card(const unsigned char &type) : data(type) {}

	//returns the numeric value of a card's type (Ace = 0, King = 12)
	unsigned char getType(void) const
	{
		return data;
	}

	//returns a random card (Ace - King)
	static Card getRandomCard(void)
	{
		unsigned char type = rand() % 13;
		return Card(type);
	}

	//get the points of a card, aces are assumed to be 1 point
	unsigned char getScore() const
	{
		const unsigned char CARD_SCORES[] =
		{
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10
		};

		return CARD_SCORES[data];
	}

	//returns the 1 or 2 character string representing a given card
	std::string getAbbreviation() const
	{
		const std::string CARD_ABBREVATIONS[] = {
			"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
		};

		return CARD_ABBREVATIONS[data];
	}

	//returns the best score possible with the given hand
	//Aces are 1 or 11 points to reach the highest score possible without busting
	static int getHandScore(const std::vector<Card> &hand, const int highestScore, bool &soft)
	{
		int aceCount = 0;
		int score = 0;

		//loop through all the cards in the current hand to calculate a score
		for (const Card &card : hand)
		{
			//keep track of how many aces are in the hand so we don't need to test for them later
			if (card.getType() == Card::Ace)
				++aceCount;
			
			//assume all aces are 1 point
			score += card.getScore();
		}

		//check if an ace is present and can changed to 11 points instead without busting
		//to support highest values higher than 21, wrap this in a loop with aceCount interations
		//soft means that a hand contains an ace treated as 11 points and therefor can accept any card without busting
		if (aceCount > 0 && score + 10 <= highestScore)
		{
			score += 10;
			soft = true;
		}
		else
			soft = false;

		return score;
	}

	//returns a string representing the hand and score of a card formatted nicely
	static std::string getHandDisplay(const std::vector<Card> &hand, const int score, const int highestScore, const bool soft)
	{
		//object that we concate strings onto, similar to std::cout
		std::stringstream ss;

		//display the contents of a hand
		ss << "Cards: ";
		for (const Card  &card : hand)
			ss << card.getAbbreviation() << " ";
		ss << std::endl;

		//display the score of a hand and it's qualities
		ss << "Score: " << score;

		//if a player receives a score of 21 with only 2 cards, that is called a blackjack
		if (score == highestScore && hand.size() == 2)
			ss << " (blackjack)";

		//if a hand is not a blackjack, test if it's soft (contains an ace values at 11 points so can safely accept another card)
		//a blackjack hand is also soft (it contains an 11 point ace), but being a blackjack is a higher display priority
		else if (soft)
			ss << " (soft)";

		//if the hand isn't a blackjack or soft, it could possibly be busted
		else if (score > highestScore)
			ss << " (bust)";

		//return the value of the stringstream object as a string for displaying in std::cout
		return ss.str();
	}
};


//call this to ignore all inputs after the user's first input and before the user pressed enter
//this prevents issues with extra inputs in prompts filling and skipping later prompts
void ingoreExtraInputs(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


//entry point to the program, hopefully we defined everything we needed
int main(void)
{
	//seed random numbers
	time_t currentTime = time(NULL);
	unsigned int seed = static_cast<unsigned int>(currentTime);
	srand(seed);

	//create the player and dealer's hand
	std::vector<Card> playerHand, dealerHand;

	//the highest value a hand can be without busting
	const int HIGHEST_SCORE = 21;

	//the character we print to represent a face down (hidden) card
	const unsigned char CARD_FACE_DOWN = static_cast<char>(178);

	//char to hold the player's response when asked to play again
	char playAgain;

	//Welcome screen
	std::cout << "Welcome to Blackjack!" << std::endl;

	do
	{
		//player receives 2 cards
		playerHand.push_back(Card::getRandomCard());
		playerHand.push_back(Card::getRandomCard());

		//dealer receives 2 cards
		dealerHand.push_back(Card::getRandomCard());
		dealerHand.push_back(Card::getRandomCard());

		//only 1 dealer card is face up
		std::cout << std::endl << "Dealer" << std::endl;
		std::cout << "Cards: " << dealerHand[0].getAbbreviation() << ' ' << CARD_FACE_DOWN << std::endl;
		//don't show the dealer's score because it is undefined

		//holds whether a hand can accept any card without busting (an ace is treated as 11 points)
		bool playerhandIsSoft;

		//display the player's complete hand, score, and state (blackjack, soft, or busted)
		int playerScore = Card::getHandScore(playerHand, HIGHEST_SCORE, playerhandIsSoft);
		std::cout << std::endl << "Player" << std::endl;
		std::cout << Card::getHandDisplay(playerHand, playerScore, HIGHEST_SCORE, playerhandIsSoft) << std::endl;

		//let the player hit until they are satisfied with their hands, reach the highest score, or bust
		char hit = 0;

		while (hit != 'n' && hit != 'N' && playerScore < HIGHEST_SCORE)
		{
			std::cout << std::endl;
			std::cout << "Hit? (Y/N): ";
			std::cin.get(hit);
			ingoreExtraInputs();

			if (hit != 'n' && hit != 'N')
			{
				playerHand.push_back(Card::getRandomCard());
				playerScore = Card::getHandScore(playerHand, HIGHEST_SCORE, playerhandIsSoft);
				std::cout << Card::getHandDisplay(playerHand, playerScore, HIGHEST_SCORE, playerhandIsSoft) << std::endl;
			}
		}

		//let the dealer hit based on the following standard shoe blackjack rules:
		//hit if the dealer's hand is less than 17 points or is a soft 17
		//the dealer follows these rules regardless of what the player's hand is, including a lower score or a blackjack
		bool dealerHandIsSoft;
		int dealerScore = Card::getHandScore(dealerHand, HIGHEST_SCORE, dealerHandIsSoft);

		while (dealerScore < 17 || (dealerScore == 17 && dealerHandIsSoft))
		{
			dealerHand.push_back(Card::getRandomCard());
			dealerScore = Card::getHandScore(dealerHand, HIGHEST_SCORE, dealerHandIsSoft);
		}

		//display the final state of the dealer's and your hands
		std::cout << std::endl;
		std::cout << std::string(10, ' ') << "Final hands" << std::endl;

		std::cout << "Dealer" << std::endl;
		std::cout << Card::getHandDisplay(dealerHand, dealerScore, HIGHEST_SCORE, dealerHandIsSoft) << std::endl;
		std::cout << std::endl;

		std::cout << "Player" << std::endl;
		std::cout << Card::getHandDisplay(playerHand, playerScore, HIGHEST_SCORE, playerhandIsSoft) << std::endl;
		std::cout << std::endl;

		//make score negative when busted and HIGHEST_SCORE + 1 when its hand is a blackjack to simplify winning logic
		//bust scores lose to any valid score and blackjack hands beat any hands totaling 21 points using more than 2 cards
		if (dealerScore > HIGHEST_SCORE)
			dealerScore = -1;
		else if (dealerScore == HIGHEST_SCORE && dealerHand.size() == 2)
			dealerScore = HIGHEST_SCORE + 1;

		if (playerScore > HIGHEST_SCORE)
			playerScore = -1;
		else if (playerScore == HIGHEST_SCORE && playerHand.size() == 2)
			playerScore = HIGHEST_SCORE + 1;

		//deplay win or lose messages
		if (playerScore > dealerScore)
			std::cout << "You win!" << std::endl;
		else if (playerScore < dealerScore)
			std::cout << "Dealer wins." << std::endl;
		else
			std::cout << "You tied with dealer." << std::endl;

		//remove all cards from all hands
		playerHand.resize(0);
		dealerHand.resize(0);

		//ask the user if they wish to play again
		std::cout << "Play again? (Y/N): ";
		std::cin.get(playAgain);
		ingoreExtraInputs();
	}
	while (playAgain != 'n' && playAgain != 'N');

	//return success
	return EXIT_SUCCESS;
}