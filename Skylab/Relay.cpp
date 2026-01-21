#include "Relay.h"

bool Relay::change = false;

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const Relay& re) {
	if (re.priorValue != re.value)
		if (Relay::change)
			os << "Relay " << re.name << " = " << re.value << "\n";
		else
			os << "Relay " << re.name << " = " << re.value << " - Prior = " << re.priorValue << "\n";
	else
		if (!Relay::change)
			os << "Relay " << re.name << " = " << re.value << "\n";

	return os; // Return the stream reference to allow chaining
}
