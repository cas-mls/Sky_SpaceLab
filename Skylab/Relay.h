#pragma once

#include <iostream>
#include <string>

class Relay
{
	public:

		enum DeviceTypes { Solenoid, RelayType, Switch };

		Relay() 
		{
			value = false;
			name = "";
		}

		Relay(std::string n, DeviceTypes type) 
		{
			value = false;
			name = n;
			switch (type)
			{
			case Solenoid:
				typeString = "sol ";
				break;
			case RelayType:
				typeString = "re ";
				break;
			case Switch:
				typeString = "sw ";
				break;
			default:
				break;
			}
		}


		Relay(const Relay& self)
		{
			name = self.name;
			value = self.value;
			typeString = self.typeString;
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
					output += typeString + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
				else
					output += typeString + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			}
			else
				if (!change)
					output += typeString + name + " = " + std::to_string(value) + ", prior = " + std::to_string(prior.value);
			return output;
		}

		std::string Print(bool prntValue)
		{
			std::string output;
			if (prntValue = value)
			{
					output += "re " + name + " = " + std::to_string(value);
			}
			return output;
		}


		operator bool& () { return value; }

		operator bool() const { return value; }

		friend std::ostream& operator<<(std::ostream& os, const Relay& p);

	private:
		bool value;
		std::string name;
		std::string typeString;
};


