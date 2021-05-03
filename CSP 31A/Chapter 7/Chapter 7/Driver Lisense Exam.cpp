/*
Purpose:
	Grade a driving test with a built in answer key

Input:
	Student's answers

Processing:
	Compare each student's answers with the answer key to see how many they got right
	Determine if the student passed

Output:
	If the student passed or failed
	number of correct answers
	number of wrong answers
	list of wrong answers

Written by Nathan Ross
Last modified 3-27-16
*/

#include <iostream> // std::cout std:cin std::streamsize
#include <limits> // std::numeric_limits<T>::max()
#include <ctype.h> // toupper()
#include <vector> //std::vector<T>
#include <cstdlib> //EXIT_SUCCESS

char getChar()
{
	char input;
	std::cin.get(input);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}

int main(void)
{
	const int PASSING_GRADE = 15;
	const int TOTAL_QUESTIONS = 20;
	const char ANSWER_SHEET[TOTAL_QUESTIONS] =
	{
		'B', 'D', 'A', 'A', 'C', 'A', 'B', 'A', 'C', 'D', 'B', 'C', 'D', 'A', 'D', 'C', 'C', 'B', 'D', 'A'
	};

	char studentAnswers[TOTAL_QUESTIONS];

	for (int i = 0; i < TOTAL_QUESTIONS; ++i)
	{
		std::cout << "Enter student's answer for question " << (i + 1) << ": ";
		char answer = toupper(getChar());

		if (answer < 'A' || answer > 'D')
		{
			std::cout << "Error. Answers must be A, B, C, or D.  Re-enter answer: ";
			answer = toupper(getChar());
		}

		studentAnswers[i] = answer;
	}

	int correctAnswers = 0;
	int incorrectAnswers = 0;
	std::vector<int> incorrectAnswerList;

	for (int i = 0; i < TOTAL_QUESTIONS; ++i)
	{
		if (studentAnswers[i] == ANSWER_SHEET[i])
			++correctAnswers;
		else
		{
			++incorrectAnswers;
			incorrectAnswerList.push_back(i);
		}
	}

	if (correctAnswers >= PASSING_GRADE)
		std::cout << "The student passed the test." << std::endl;
	else
		std::cout << "The student failed the test." << std::endl;

	std::cout << "Correct answers: " << correctAnswers << " / " << TOTAL_QUESTIONS << std::endl;
	std::cout << "Incorrect answers: " << incorrectAnswers << " / " << TOTAL_QUESTIONS << std::endl;

	if (incorrectAnswers > 0)
	{
		std::cout << "List of incorrect answers:" << std::endl;
		for (int i = 0; i < incorrectAnswers; ++i)
		{
			int questionIndex = incorrectAnswerList[i];
			std::cout << "Question " << (questionIndex + 1) << ":\tStudent: " << studentAnswers[questionIndex] << "\tAnswer: " << ANSWER_SHEET[questionIndex] << std::endl;
		}
	}

	system("pause");
	return EXIT_SUCCESS;
}