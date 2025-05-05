#ifndef POSITION_H
#define POSITION_H

#define GraphicRender true
#include "memtrace.h"
#include <cmath>

bool doubleEQ(double a, double b);

class Position {
	double x;
	double y;
public:
	Position(double x = 0, double y = 0) : x(x), y(y) {}
	double getX() { return x; }
	double getY() { return y; }
	bool operator==(Position p) {
		if (doubleEQ(x, p.getX()) && doubleEQ(y, p.getY())) return true;
		return false;
	}
	Position operator+ (Position p) {
		return Position(x + p.getX(), y + p.getY());
	}
	Position operator- (Position p) {
		return Position(x - p.getX(), y - p.getY());
	}
	Position operator+= (Position p) {
		x += p.getX();
		y += p.getY();
		return *this;
	}
};

#endif // POSITION_H