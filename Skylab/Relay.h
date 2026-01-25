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
			name = "";
		}

		Relay(std::string n) 
		{
			value = false;
			name = n;
		}


		Relay(const Relay& self)
		{
			name = self.name;
			value = self.value;
		}


		~Relay() {}


		void Assign(Relay self)
		{
			name = self.name;
			value = self.value;
		}

		bool operator=(const bool val)
		{
			value = val;
			return value;
		}

		std::string Print(Relay prior, bool change)
		{
			std::string output;
			if (prior.value != value)
			{
				if (change)
					output += "re " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
				else
					output += "re " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			}
			else
				if (!change)
					output += "re " + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			return output;
		}


		operator bool& () { return value; }

		operator bool() const { return value; }

		friend std::ostream& operator<<(std::ostream& os, const Relay& p);

	private:
		bool value;
		std::string name;
};


