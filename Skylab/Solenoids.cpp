#include "Solenoids.h"

bool Solenoids::change = false;

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const Solenoids& re) {
	if (re.priorValue != re.value)
		if (Solenoids::change)
			os << "Solenoids " << re.name << " = " << re.value << "\n";
		else
			os << "Solenoids " << re.name << " = " << re.value << " - Prior = " << re.priorValue << "\n";
	else
		if (!Solenoids::change)
			os << "Solenoids " << re.name << " = " << re.value << "\n";

	return os; // Return the stream reference to allow chaining
}
