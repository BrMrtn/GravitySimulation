#ifndef PLANETARY_OBJECT_H
#define PLANETARY_OBJECT_H

#include <iostream>
#include "Vector.h"
#include <vector>

#define Grav_const 0.000000000066743 //gravitációs állandó

class PlanetaryObject {
protected:
	Position position;
	Vector velocity;
	Vector acceleration;
	double mass;
	double radius;
	bool isConstant;

public:
	PlanetaryObject();
	PlanetaryObject(Position position, Vector velocity, double mass, double radius, bool isConstant);

	Position getPosition() { return position; }
	virtual void setPosition(Position p) { position = p; }

	Vector getVelocity() { return velocity; }
	void setVelocity(Vector v) { velocity = v; }
	void setVelocity(double x, double y) { velocity = Vector(x, y); }

	Vector getAcceleration() { return acceleration; }
	void setAcceleration(Vector a) { acceleration = a; }

	double getMass() { return mass; }
	void setMass(double m) { mass = m; }

	double getRadius() { return radius; }
	virtual void setRadius(double r) { radius = r; }

	bool getIsConstant() { return isConstant; }
	void setIsConstant(bool c) { isConstant = c; }

	double getDistance(PlanetaryObject p);
	Vector ParticularAcceleration(PlanetaryObject p);

	bool isOutOfScreen();
	bool operator==(PlanetaryObject p);
	bool operator!= (PlanetaryObject p) { return !(*this == p); }
};

#endif // PLANETARY_OBJECT_H

