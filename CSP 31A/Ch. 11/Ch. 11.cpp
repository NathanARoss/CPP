/*
Purpose:
	Record test scores of a class and calculate averages and grades

Input:
	Number of students
	Number of tests scored

	For each student
		Name
		ID
		For each test assigned
			Test score

Processing:
	Dynamically allocate array of students
	Dynamically allocate array of test scores for each student
	Calculate average test score and student grade

Output:
	For each student:
		Name
		ID
		Average test score
		Grade

Written by Nathan Ross
Last modified 5/1/16
*/

#include <iostream> // std::cout std::cin
#include <iomanip>  // std::fixed std::showpoint std::setprecision
#include <string>   // std::string
#include <limits>   // std::numeric_limits<T>::max()
#include <cstdlib>  // EXIT_SUCCESS

//input the given type from cin, sets error to true if error parsing
template <typename type>
type inputType(bool &error);

//return letter grade of a score
char getScoreGrade(float score);

//struct for holding basic student information
struct Student
{
	std::string name;
	long long int ID;
	float *testScores;
	float averageScore;
	char grade;
};

//entry point
int main(void)
{
	//format when displaying test scores, ex 99.9%
	std::cout << std::fixed << std::showpoint << std::setprecision(1);

	//number of students, must be at least 1
	std::cout << "Enter number of students: ";
	bool error;
	int studentCount = inputType<int>(error);

	while (error || studentCount <= 0)
	{
		std::cout << "Error. Enter a positive number of students: ";
		studentCount = inputType<int>(error);
	}

	//number of tests, must be at least 1
	std::cout << "Enter number of tests scored: ";
	int testCount = inputType<int>(error);

	while (error || testCount <= 0)
	{
		std::cout << "Error. Enter a positive number of tests: ";
		testCount = inputType<int>(error);
	}

	//allocate array of students
	Student *students = new Student[studentCount];

	//allocate storage for tests
	for (int i = 0; i < studentCount; ++i)
		students[i].testScores = new float[testCount];

	//begin inputing student information
	for (int i = 0; i < studentCount; ++i)
	{
		std::cout << std::endl;
		std::cout << "Student #" << i << std::endl;

		//Name
		std::cout << "Enter name: ";
		std::getline(std::cin, students[i].name);

		//ID, must be 0 or greater
		std::cout << "Enter ID: ";
		students[i].ID = inputType<long long int>(error);

		while (error || students[i].ID < 0)
		{
			std::cout << "Error. Enter positive ID: ";
			students[i].ID = inputType<long long int>(error);
		}

		//Test scores, each must be 0 or greater (extra credit is allowed)
		for (int t = 0; t < testCount; ++t)
		{
			std::cout << "Enter score for test #" << t << ": ";
			students[i].testScores[t] = inputType<float>(error);

			while (error || students[i].testScores[t] < 0.0f)
			{
				std::cout << "Error. Enter positive score for test #" << t << ": ";
				students[i].testScores[t] = inputType<float>(error);
			}
		}

		//average test scores
		float totalScore = 0.0;

		for (int t = 0; t < testCount; ++t)
			totalScore += students[i].testScores[t];

		students[i].averageScore = totalScore / static_cast<float>(testCount);

		//grade
		students[i].grade = getScoreGrade(students[i].averageScore);
	}

	//display student grades
	for (int i = 0; i < studentCount; ++i)
	{
		std::cout << std::endl;
		std::cout << "Student ID:\t" << students[i].ID << std::endl;
		std::cout << "Student name:\t" << students[i].name << std::endl;
		std::cout << "Average score:\t" << students[i].averageScore << '%' << std::endl;
		std::cout << "Student grade:\t" << students[i].grade << std::endl;
	}

	//free resources
	for (int i = 0; i < studentCount; ++i)
		delete[] students[i].testScores;

	delete[] students;

	return EXIT_SUCCESS;
}

template <typename type>
type inputType(bool &error)
{
	type input;
	std::cin >> input;

	if (std::cin.fail()) //detect failure to parse type
	{
		error = true;
		std::cin.clear(); //remove error flag
	}
	else
		error = false;

	//ignore extra input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}

char getScoreGrade(float score)
{
	char grade;

	if (score < 60.0f)
		grade = 'F';
	else if (score < 70.0f)
		grade = 'D';
	else if (score < 80.0f)
		grade = 'C';
	else if (score < 90.0f)
		grade = 'B';
	else
		grade = 'A';

	return grade;
}