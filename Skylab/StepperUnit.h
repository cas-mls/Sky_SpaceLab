#pragma once

#include <iostream>
#include <string>

class StepperUnit
{
	public:

		enum stepperTypes {Up, UpDown, Continuous};

		static bool change;

		StepperUnit() {
			limit = 0;
			endOfStroke = false;
			priorEndOfStroke = false;
			value = 0;
			priorValue = 0;
			name = "";
			stepType = Up;
		}

		StepperUnit(std::string n, int Limit, stepperTypes steptype = Up) {
			limit = Limit;
			endOfStroke = false;
			priorEndOfStroke = false;
			value = 0;
			priorValue = 0;
			name = n;
			stepType = steptype;
		}
		~StepperUnit()
		{
		}
		void reset()
		{
			endOfStroke = false;
			value = 0;
		}

		std::string to_string() const
		{
			return std::to_string(value);
		}

		void ResetEos()
		{
			if (endOfStroke)
			{
				endOfStroke = false;
			}
		}

		int Value() const
		{
			return value;
		}

		bool eos() const
		{
			return endOfStroke;
		}

		bool operator==(const int value) const 	{ return this->value == value; }

		bool operator>(const int value) const { return this->value > value; }

		bool operator!=(const int value) const 	{ return this->value != value; }

		bool operator%(const int value) const { return this->value % value; }

		int operator++(int) 
		{ 
			if (value < limit)
			{
				priorValue = value;
				priorEndOfStroke = endOfStroke;
				endOfStroke = true;
				return value++;
			}
			else
				if (stepType == Continuous)
				{
					priorEndOfStroke = endOfStroke;
					priorValue = value;
					value = 0;
					endOfStroke = true;
					return value;
				}
				else
				{
					return value;
				}
		}

		int operator--(int)
		{
			if (value > 0 && stepType == UpDown)
			{
				endOfStroke = true;
				return value--;
			}
			else
				return value;
		}

		int operator=(const int value) { return value; }

		operator int& () { return value; }

		operator int() const { return value; }

		friend std::ostream& operator<<(std::ostream& os, const StepperUnit& p);

	private:
		int value;
		int priorValue;
		bool endOfStroke;
		bool priorEndOfStroke;
		int limit;
		std::string name;
		stepperTypes stepType;
};


