#pragma once

#include <iostream>
#include <string>

class Relay
{
	public:
		static bool change;

		Relay() 
		{
			value = false;
			priorValue = false;
			name = "";
		}

		Relay(std::string n) 
		{
			value = false;
			priorValue = false;
			name = n;
		}

		~Relay() {}

		bool operator=(const bool val)
		{
			priorValue = value;
			value = val;
			return value;
		}

		operator bool& () { return value; }

		operator bool() const { return value; }

		friend std::ostream& operator<<(std::ostream& os, const Relay& p);

	private:
		bool value;
		bool priorValue;
		std::string name;
};

// Overload the << operator
//std::ostream& operator<<(std::ostream& os, const Relay& re) {
//	os << "**" << re.name << ": " << re.value;
//	return os; // Return the stream reference to allow chaining
//}

