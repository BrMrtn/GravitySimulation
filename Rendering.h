#ifndef RENDERING_H
#include "PlanetaryObject.h"
#if GraphicRender
#define RENDERING_H
#include <SFML/Graphics.hpp>


//planetary object-ek alosztályai, amika a megjelenítésért felelnek
class RenderPlanetaryObject : public PlanetaryObject {
public:
	sf::CircleShape render_shape;

	void setPosition(Position p) {
		position = p;
		render_shape.setPosition(sf::Vector2f(p.getX(), p.getY()) - sf::Vector2f(radius, radius));
	}
	void setRadius(double r) {
		radius = r;
		render_shape.setRadius(r);
	}
	RenderPlanetaryObject() : PlanetaryObject() {
		render_shape.setRadius(0);
	}
	RenderPlanetaryObject(PlanetaryObject p) : PlanetaryObject(p) {
		render_shape.setRadius(p.getRadius());
	}
	RenderPlanetaryObject(Position position, Vector velocity, double mass, double radius, bool isConstant) :
		PlanetaryObject(position, velocity, mass, radius, isConstant) {
		render_shape.setRadius(radius);
	}
};

void UpdatePositions(std::vector<RenderPlanetaryObject>& rendered_space);

void RenderObjects(std::vector<PlanetaryObject> s);

#endif // GraphicRender
#endif // RENDERING_H