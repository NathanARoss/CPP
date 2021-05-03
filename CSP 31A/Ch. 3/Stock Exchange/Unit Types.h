#pragma once

namespace unit {
	class Amount
	{
		double amount;
	public:
		Amount() {}
		Amount(double amount) : amount(amount) {}

		Amount& operator=(const double &amount)
		{
			this->amount = amount;
			return *this;
		}

		double getValue()
		{
			return amount;
		}
	};

	class Currency
	{
		double currency;
	public:
		Currency() {}
		Currency(double currency) : currency(currency) {}

		Currency& operator=(const double &currency)
		{
			this->currency = currency;
			return *this;
		}

		//return the currency times the rate, needed to take 2% of the totals
		Currency operator*(const double& rate)
		{
			return Currency(currency * rate);
		}

		Currency operator+(const Currency& addend)
		{
			double sum = currency + addend.currency;
			return Currency(sum);
		}

		Currency operator-(const Currency& subtrahend)
		{
			double difference = currency - subtrahend.currency;
			return Currency(difference);
		}

		double getValue()
		{
			return currency;
		}
	};

	//rate of change between currency and amount
	class Cost
	{
		double cost;
	public:
		Cost() {}
		Cost(double cost) : cost(cost) {}

		Cost& operator=(const double &cost)
		{
			this->cost = cost;
			return *this;
		}

		//conversion operator
		Currency operator*(Amount& amount)
		{
			return Currency(amount.getValue() * cost);
		}

		//conversion operator
		Amount operator/(Currency& currency)
		{
			return Amount(currency.getValue() / cost);
		}

		double getValue()
		{
			return cost;
		}
	};
}