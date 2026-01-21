#pragma once

#include <iostream>
#include <string>

class Solenoids
{

public:
	static bool change;

	Solenoids()
	{
		value = false;
		priorValue = false;
		name = "";
	}

	Solenoids(std::string n)
	{
		value = false;
		priorValue = false;
		name = n;
	}

	~Solenoids() {}

	bool operator=(const bool val)
	{
		priorValue = value;
		value = val;
		return value;
	}

	//operator bool& () { return value; }

	//operator bool() const { return value; }

	friend std::ostream& operator<<(std::ostream& os, const Solenoids& p);

private:
	bool value;
	bool priorValue;
	std::string name;
};


