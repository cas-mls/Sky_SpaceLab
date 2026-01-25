#include "Relay.h"

bool Relay::change = false;

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const Relay& re) {
	
	os << re.name << " re = " << re.value << "\n";

	return os; // Return the stream reference to allow chaining
}
