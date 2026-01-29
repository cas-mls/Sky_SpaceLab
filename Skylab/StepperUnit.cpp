#include "StepperUnit.h"


// Overload the << operator
std::ostream& operator<<(std::ostream& os, const StepperUnit& stepper) {
	bool test = stepper.name == "scoreMotor";
	os << stepper.name << " stp = " << stepper.value;
	os << stepper.name << " eos = " << stepper.endOfStroke;

	return os; // Return the stream reference to allow chaining
}
