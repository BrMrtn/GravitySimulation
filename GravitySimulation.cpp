#include "memtrace.h"
#include "DisplayOnConsole.h"
#if GraphicRender
    #include "Rendering.h"
#endif // GraphicRender

#ifndef MEMTRACE
#error "MEMTRACE not defined!"
#endif // MEMTRACE

//minden ezerszer kisebb legyen, mint a val�s�gban

int main() {
    //szimul�ci� ter�nek l�trehoz�sa
    std::vector<PlanetaryObject> space;
    
    //Egy stabil k�rp�ly�n mozg� bolyg� �s k�z�ppontj�nak adatai (kipr�b�l�shoz el�g kit�r�lni a komment jeleket)
    /*PlanetaryObject sun(Position(950, 500), Vector(Position(0, 0)), 20975982500000, 20, false);
    space.push_back(sun);
    PlanetaryObject earth(Position(1200, 500), Vector(Position(0, sqrt(5.6))), 10000000, 15, false);
    space.push_back(earth);*/

    //Grafikus megjelen�t�s
#if GraphicRender
    RenderObjects(space);
#else
    //Console-os megjelen�t�s
    int choosen;
    int time;
    bool MenuIsActive = true;
    while (MenuIsActive) {
        DisplayMenu(std::cout);
        std::cin >> choosen;
        std::cout << "***************************\n";
        switch (choosen) {
        case 1: //�j objektum hozz�ad�sa
            AddObjectToSpace(space);
            break;
        case 2: //objektumok ki�r�sa alap�llapotban
            DisplayObjects(space, 0);
            break;
        case 3: //objektumok ki�r�sa <x> m�sodperc eltelt�vel
            GetTime(time);
            DisplayObjects(space, time);
            break;
        case 4: //kil�p�s
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