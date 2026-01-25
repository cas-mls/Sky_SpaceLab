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
			value = 0;
			name = "";
			stepType = Up;
		}

		StepperUnit(std::string n, int Limit, stepperTypes steptype = Up) {
			limit = Limit;
			endOfStroke = false;
			value = 0;
			name = n;
			stepType = steptype;
		}
		~StepperUnit()
		{
		}

		StepperUnit(const StepperUnit &self)
		{
			name = self.name;
			value = self.value;
			endOfStroke = self.endOfStroke;
			stepType = self.stepType;
			limit = self.limit;
		}

		void Assign(StepperUnit self)
		{
			bool test = self.name == "scoreMotor";
			name = self.name;
			value = self.value;
			//	eos		new.eof	next.eof
			//	1		1			0
			//	1		0			0
			//	0		1			1
			//	0		0			0
			if (endOfStroke && self.endOfStroke)
				endOfStroke = false;
			else 
				endOfStroke = self.endOfStroke;
			stepType = self.stepType;
			limit = self.limit;
		}

		void AssignEos(StepperUnit self)
		{
			bool test = self.name == "scoreMotor";
			endOfStroke = self.endOfStroke;
		}

		void reset()
		{
			endOfStroke = false;
			value = 0;
		}

		std::string Print(StepperUnit prior, bool change)
		{
			std::string output;
			if (prior.value != value)
			{
				if (change)
					output += "stp " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
				else
					output += "stp " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			}
			else
				if (!change)
					output += "stp " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			return output;
		}

		std::string PrintEos(StepperUnit prior, bool change)
		{
			std::string output;
			if (prior.endOfStroke != endOfStroke)
			{
				if (change)
					output += "eos " + name + " = " + std::to_string(endOfStroke) + ", prior = " + std::to_string(prior.endOfStroke);
				else 
					output += "eos " + name + " = " + std::to_string(endOfStroke) + ", prior = " + std::to_string(prior.endOfStroke);
			}
			else
				if (!change)
					output += "eos " + name + " = " + std::to_string(endOfStroke) + ", prior = " + std::to_string(prior.endOfStroke);
			return output;
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
			if (endOfStroke) return value;

			if (value < limit)
			{
				endOfStroke = true;
				return value++;
			}
			else
				if (stepType == Continuous)
				{
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
			if (endOfStroke) return value;

			if (value > 0 && stepType == UpDown)
			{
				endOfStroke = true;
				return value--;
			}
			else
				return value;
		}

		int operator=(const int val) 
		{ 
			value = val;
			return val;
		}

		operator int& () { return value; }

		operator int() const { return value; }

		friend std::ostream& operator<<(std::ostream& os, const StepperUnit& p);

	private:
		int value;
		bool endOfStroke;
		int limit;
		std::string name;
		stepperTypes stepType;
};


