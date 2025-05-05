#ifndef VECTOR_H
#define VECTOR_H

#include "Position.h"

class Vector {
	Position direction;
public:
	Vector() : direction(Position(0, 0)) {}
	Vector(Position p) : direction(p) {}
	Vector(double x, double y) : direction(Position(x, y)) {}
	void setDirection(Position p) { direction = p; }
	Position getDirection() { return direction; }
	double getMagnitude() {
		return sqrt(direction.getX()*direction.getX() + direction.getY()*direction.getY());
	}
	bool operator==(Vector v) {
		return (direction == v.getDirection());
	}
	Vector operator+(Vector v) {
		return Vector(direction + v.getDirection());
	}
	Vector operator+=(Vector v) {
		direction += v.getDirection();
		return *this;
	}
};

#endif // VECTOR_H

