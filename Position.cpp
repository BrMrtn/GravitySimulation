#include "Position.h"

bool doubleEQ(double a, double b) {
	if (abs(a - b) < 0.0000000001) return true;
	return false;
}