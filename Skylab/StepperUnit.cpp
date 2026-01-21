#include "StepperUnit.h"

bool StepperUnit::change = false;

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const StepperUnit& stepper) {
	if (stepper.priorValue != stepper.value)
		if (StepperUnit::change)
			os << "Stepper " << stepper.name << " = " << stepper.value << "\n";
		else
			os << "Stepper " << stepper.name << " = " << stepper.value << " - Prior = " << stepper.priorValue << "\n";
	else
		if (!StepperUnit::change)
			os << "Stepper " << stepper.name << " = " << stepper.value << "\n";

	if (stepper.priorEndOfStroke != stepper.endOfStroke)
		if (StepperUnit::change)
			os << "Stepper EOS " << stepper.name << " = " << stepper.endOfStroke << "\n";
		else
			os << "Stepper EOS " << stepper.name << " = " << stepper.endOfStroke << " - Prior = " << stepper.priorEndOfStroke << "\n";
	else
		if (!StepperUnit::change)
			os << "Stepper EOS " << stepper.name << " = " << stepper.endOfStroke << "\n";

	return os; // Return the stream reference to allow chaining
}
