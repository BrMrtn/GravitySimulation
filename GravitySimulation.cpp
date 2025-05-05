#include "memtrace.h"
#include "DisplayOnConsole.h"
#if GraphicRender
    #include "Rendering.h"
#endif // GraphicRender

#ifndef MEMTRACE
#error "MEMTRACE not defined!"
#endif // MEMTRACE

//minden ezerszer kisebb legyen, mint a valóságban

int main() {
    //szimuláció terének létrehozása
    std::vector<PlanetaryObject> space;
    
    //Egy stabil körpályán mozgó bolygó és középpontjának adatai (kipróbáláshoz elég kitörölni a komment jeleket)
    /*PlanetaryObject sun(Position(950, 500), Vector(Position(0, 0)), 20975982500000, 20, false);
    space.push_back(sun);
    PlanetaryObject earth(Position(1200, 500), Vector(Position(0, sqrt(5.6))), 10000000, 15, false);
    space.push_back(earth);*/

    //Grafikus megjelenítés
#if GraphicRender
    RenderObjects(space);
#else
    //Console-os megjelenítés
    int choosen;
    int time;
    bool MenuIsActive = true;
    while (MenuIsActive) {
        DisplayMenu(std::cout);
        std::cin >> choosen;
        std::cout << "***************************\n";
        switch (choosen) {
        case 1: //új objektum hozzáadása
            AddObjectToSpace(space);
            break;
        case 2: //objektumok kiírása alapállapotban
            DisplayObjects(space, 0);
            break;
        case 3: //objektumok kiírása <x> másodperc elteltével
            GetTime(time);
            DisplayObjects(space, time);
            break;
        case 4: //kilépés
            MenuIsActive = false;
            break;
        default: 
            std::cout << "Not a valid number, choose again: ";
            std::cin >> choosen;
            break;
        }
    }

#endif // GraphicRender

    return 0;
}