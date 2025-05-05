#include "PlanetaryObject.h"

PlanetaryObject::PlanetaryObject() : position(Position(0, 0)), velocity(Vector()), acceleration(Vector()), mass(0), radius(0) {}

PlanetaryObject::PlanetaryObject(Position position, Vector velocity, double mass, double radius, bool isConstant) :
	position(position), velocity(velocity), mass(mass), radius(radius), isConstant(isConstant) {}

double PlanetaryObject::getDistance(PlanetaryObject p) {
	double x_distance = abs(position.getX() - p.getPosition().getX());
	double y_distance = abs(position.getY() - p.getPosition().getY());
	return sqrt(x_distance * x_distance + y_distance * y_distance);
}

//egy bolygó által az adott objektumra kifejtett erõbõl adódó gyorsulást adja vissza
Vector PlanetaryObject::ParticularAcceleration(PlanetaryObject p) {
	double distance = getDistance(p);
	Vector acceleration(0, 0);
	if (distance <= 1) return acceleration; //véletlenül se következzen be a 0-val osztás
	double magnitude = Grav_const * p.getMass() / (distance * distance);
	double X = p.getPosition().getX() - position.getX();
	double Y = p.getPosition().getY() - position.getY();
	double hypotenuse = sqrt(X * X + Y * Y);
	double ratio = magnitude / hypotenuse;
	X = X * ratio;
	Y = Y * ratio;
	acceleration.setDirection(Position(X, Y));
	return acceleration;
}

bool PlanetaryObject::operator==(PlanetaryObject p) {
	if (position == p.getPosition() &&
		velocity == p.getVelocity() &&
		acceleration == p.getAcceleration() &&
		mass == p.getMass() &&
		radius == p.getRadius())
		return true;
	return false;
}

bool PlanetaryObject::isOutOfScreen() {
	int offset = 2 * radius; // hogy csak azután tûnjön el, hogy ténylegesen elhagyta az ablakot
	if (position.getX() < 0 - offset || position.getX() > 1920 + offset || position.getY() < 0 - offset || position.getY() > 1080 + offset)
		return true;
	return false;
}