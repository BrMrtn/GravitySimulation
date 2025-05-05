#ifndef DISPLAYONCONSOLE_H
#define DISPLAYONCONSOLE_H

#include "PlanetaryObject.h"

void WriteObjectData(PlanetaryObject p, std::ostream& os);

void DisplayMenu(std::ostream& os);

void AddObjectToSpace(std::vector<PlanetaryObject>& space);

void GetTime(int& time);

void UpdatePositions(std::vector<PlanetaryObject>& space);

void DisplayObjects(std::vector<PlanetaryObject> space, int sec);

#endif // DISPLAYONCONSOLE_H

