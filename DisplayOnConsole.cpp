#include "DisplayOnConsole.h"

//objektum adatainak kiírása
void WriteObjectData(PlanetaryObject p, std::ostream& os) {
    os << "Mass: " << p.getMass() << " kg\n"
        << "Radius: " << p.getRadius() << " m\n"
        << "Position: (" << p.getPosition().getX() << ", " << p.getPosition().getY() << ")\n"
        << "Velocity: " <<p.getVelocity().getMagnitude() << " m/s (" << p.getVelocity().getDirection().getX() << ", " <<p.getVelocity().getDirection().getY() << ")\n"
        << "Acceleration: " << p.getAcceleration().getMagnitude() << " m/s (" << p.getAcceleration().getDirection().getX() << ", " << p.getAcceleration().getDirection().getY() << ")\n"
        << "IsConstant: " << p.getIsConstant() << "\n" << std::endl;
}

//menü kiírása
void DisplayMenu(std::ostream& os) {
    os << "***************************\n"
        << "1. Add new object to space\n"
        << "2. Display all objects default state\n"
        << "3. Display all objects state <x> seconds after start\n"
        << "4. Quit\n"
        << "To choose from the options, write a number: " << std::endl;
}


//idõ bekérése
void GetTime(int& time) {
    std::cout << "Seconds passed:";
    std::cin >> time;
}

//objektumok hozzáadása a szimulációhoz
void AddObjectToSpace(std::vector<PlanetaryObject>& space) {
    PlanetaryObject p;
    std::cout << "Enter the new object's properties:\n";
    double data1, data2;
    std::cout << "Mass: ";
    std::cin >> data1;
    p.setMass(data1);

    std::cout << "Radius: ";
    std::cin >> data1;
    p.setRadius(data1);

    std::cout << "X position: ";
    std::cin >> data1;
    std::cout << "Y position: ";
    std::cin >> data2;
    p.setPosition(Position (data1, data2));

    std::cout << "X velocity: ";
    std::cin >> data1;
    std::cout << "Y velocity: ";
    std::cin >> data2;
    p.setVelocity(data1, data2);

    char isconstant;
    std::cout << "Is this planet in constant state? (y/anything else): ";
    std::cin >> isconstant;

    p.setIsConstant(isconstant=='y');
    if (p.getIsConstant()) p.setVelocity(0, 0);

    space.push_back(p);
    std::cout << "New object added successfully!\n";
}

//objektumok állapotának frissítése
void UpdatePositions(std::vector<PlanetaryObject>& space) {
    for (PlanetaryObject& pi : space) {
        Vector temp_acceleration;
        for (PlanetaryObject& pj : space) {
            if (pi != pj)
                temp_acceleration += pi.ParticularAcceleration(pj);
        }
        pi.setAcceleration(temp_acceleration);
        pi.setVelocity(pi.getVelocity() + pi.getAcceleration());
        pi.setPosition(pi.getPosition() + pi.getVelocity().getDirection());
        if (pi.isOutOfScreen())
            space.erase(std::remove(space.begin(), space.end(), pi), space.end());
    }
}

//objektumok állapotának kiírása x másodperccel a szimuláció kezdete után
void DisplayObjects(std::vector<PlanetaryObject> space, int sec) {
    for (int i = 0; i < sec; i++)
        UpdatePositions(space);
    for (PlanetaryObject& pi : space)
        WriteObjectData(pi, std::cout);
    if(space.empty())
		std::cout << "No objects left in space!\n";
}

