#include "StepperUnit.h"

bool StepperUnit::change = false;

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const StepperUnit& stepper) {
	bool test = stepper.name == "scoreMotor";
	os << stepper.name << " stp = " << stepper.value << "\n";
	os << stepper.name << " eos = " << stepper.endOfStroke << "\n";

	return os; // Return the stream reference to allow chaining
}
