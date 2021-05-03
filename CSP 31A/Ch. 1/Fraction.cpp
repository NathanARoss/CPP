/*
Fraction is a datatype that can perfectly represent sificiently simple or small real numbers

*/

#include <algorithm>

class Fraction
{
private:
	int numerator, denominator;

	static bool isFactor(int numerator, int denominator, int factor)
	{
		return ((numerator % factor == 0) && (denominator % factor == 0));
	}

	//basic math functions
	static Fraction multiply(const Fraction &a, const Fraction &b)
	{
		int numerator = a.numerator * b.numerator;
		int denominator = a.denominator * b.denominator;
		Fraction product = Fraction(numerator, denominator);
		Fraction simplifiedProduct = simplify(product);
		return simplifiedProduct;
	}

	static Fraction add(const Fraction &a, const Fraction &b)
	{
		//find common denominator
		Fraction first = Fraction(a.numerator * b.denominator, a.denominator * b.denominator);
		Fraction second = Fraction(b.numerator * a.denominator, a.denominator * b.denominator);
		Fraction sum = Fraction(first.numerator + second.numerator, first.denominator);

		Fraction simplifedSum = Fraction::simplify(sum);
		return simplifedSum;
	}

	//find and divide by common factors
	static Fraction simplify(const Fraction &fraction)
	{
		Fraction simplified = fraction;

		//denominator should be positive
		if (simplified.denominator < 0)
		{
			//flip the sign of numerator and denominator
			simplified = simplified * Fraction(-1, -1);
		}

		//a common factor can only be as big as the smallest number
		int smallerValue = std::min(simplified.numerator, simplified.denominator);

		int factor = 2;
		while (factor <= smallerValue)
		{
			if (isFactor(simplified.numerator, simplified.denominator, factor))
			{
				simplified.numerator /= factor;
				simplified.denominator /= factor;
				smallerValue = std::min(simplified.numerator, simplified.denominator);
			}
			else
			{
				//factors can appear more than once, so only proceed if the current one is ruled out
				++factor;
			}
		}

		return simplified;
	}

public:
	//constructor
	Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}


	int getNumerator()
	{
		return numerator;
	}

	int getDenominator()
	{
		return denominator;
	}

	//divide numerator by denominator and return float rounded to the nearest cent
	float getSinglePrecisionCurrency()
	{
		float value = (float)numerator / (float)denominator;
		value = std::round(value * 100.0f) / 100.0f;
		return value;
	}

	//divide numerator by denominator and return double rounded to the nearest cent
	double getDoublePrecisionCurrency()
	{
		double value = (double)numerator / (double)denominator;
		value = std::round(value * 100.0) / 100.0;
		return value;
	}


	void setNumerator(int numerator)
	{
		this->numerator = numerator;
		*this = simplify(*this);
	}

	void setDenominator(int denominator)
	{
		this->denominator = denominator;
		*this = simplify(*this);
	}

	void setValue(int numerator, int denominator)
	{
		this->numerator = numerator;
		this->denominator = denominator;
		*this = simplify(*this);
	}


	//operator overloading
	Fraction operator-()
	{
		return Fraction(-this->numerator, this->denominator);
	}

	Fraction operator+(const Fraction& a)
	{
		return Fraction::add(*this, a);
	}

	Fraction operator-(const Fraction& a)
	{
		//I need to make a non-const copy to use the negation operator
		Fraction secondOperand = a;
		return Fraction::add(*this, -secondOperand);
	}

	Fraction operator*(const Fraction& a)
	{
		return Fraction::multiply(*this, a);
	}

	Fraction operator/(const Fraction& a)
	{
		Fraction reciprocal = Fraction(a.denominator, a.numerator);
		return Fraction::multiply(*this, reciprocal);
	}

	//integer versions of the operators
	Fraction operator+(const int& a)
	{
		return *this + Fraction(a, 1);
	}

	Fraction operator-(const int& a)
	{
		return *this - Fraction(a, 1);
	}

	Fraction operator*(const int& a)
	{
		return *this * Fraction(a, 1);
	}

	Fraction operator/(const int& a)
	{
		return *this / Fraction(a, 1);
	}
};