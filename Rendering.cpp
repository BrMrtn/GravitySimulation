#include "Position.h"
#if GraphicRender
#include <iostream>
#include "Rendering.h"

//minden ezerszer kisebb legyen, mint a val�s�gban
void UpdatePositions(std::vector<RenderPlanetaryObject>& rendered_space) {
    for (RenderPlanetaryObject& pi : rendered_space) {
        Vector temp_acceleration;
        for (RenderPlanetaryObject& pj : rendered_space) {
            if (pi != pj) {
                if (pi.getDistance(pj) < pi.getRadius()) { //�tk�z�s
                    if(pi.getIsConstant()) rendered_space.erase(std::remove(rendered_space.begin(), rendered_space.end(), pj), rendered_space.end());
                    else if(pj.getIsConstant()) rendered_space.erase(std::remove(rendered_space.begin(), rendered_space.end(), pi), rendered_space.end());
                    else {
                        rendered_space.erase(std::remove(rendered_space.begin(), rendered_space.end(), pi), rendered_space.end());
                        rendered_space.erase(std::remove(rendered_space.begin(), rendered_space.end(), pj), rendered_space.end());
                    }
                    
                } else
                    temp_acceleration += pi.ParticularAcceleration(pj); //ered� gyorsul�s kisz�m�t�sa
            }
        }
        if (!pi.getIsConstant()) {
            pi.setAcceleration(temp_acceleration);
            pi.setVelocity(pi.getVelocity() + pi.getAcceleration());
            pi.setPosition(pi.getPosition() + pi.getVelocity().getDirection());
        }
        if (pi.isOutOfScreen()) {
            rendered_space.erase(std::remove(rendered_space.begin(), rendered_space.end(), pi), rendered_space.end());
        }
    }
    rendered_space.shrink_to_fit(); //mem�ria felszabad�t�sa
}

void RenderObjects(std::vector<PlanetaryObject> s) {
    //szimul�lt objektumok �tkonvert�l�sa
    std::vector<RenderPlanetaryObject> space;
    for (PlanetaryObject& po : s) {
		space.push_back(RenderPlanetaryObject(po));
	}
    
    //ablak l�trehoz�sa
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GravitySimulation");
    window.setFramerateLimit(60);

    //el�n�zet l�trehoz�sa
    RenderPlanetaryObject preview(Position(0, 0), Vector(Position(0, 0)), 10000000000000, 10, false);
    preview.render_shape.setFillColor(sf::Color(255, 255, 255, 128));
    
    //hogy ne legyenek minden ciklusban �jra deklar�lva
    bool charging = false;
    bool placeable = true;
    std::string isConstant = "false";
    RenderPlanetaryObject aim(Position(0, 0), Vector(Position(0, 0)), 0, 3, true);
    aim.render_shape.setFillColor(sf::Color::Red);
    sf::Vertex line[2];
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    //preview adatai (k�s�bb ki�rjuk)
    sf::String preview_data;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font); 
    text.setCharacterSize(20);
    text.setFillColor(sf::Color(255, 255, 255, 128));

    //�llapotfriss�t�s
    while (window.isOpen()) {
        //v�ltoz�k alaphelyzetbe �ll�t�sa
        preview.render_shape.setFillColor(sf::Color(255, 255, 255, 128));
        placeable = true;

        //esem�nyek kezel�se
        sf::Event event;
        while (window.pollEvent(event)) {
            //ablak bez�r�sa
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            //bal eg�rgomb lenyom�s�ra c�lz�pont megjelen�t�se
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                charging = true;
                aim.setPosition(preview.getPosition());
            }
            //ha le van nyomva a bal eg�rgomb
            if (charging) {
                //l�tez� objektum hely�re nem rakhatunk �jat
                for (RenderPlanetaryObject& pi : space) {
                    if (preview.getDistance(pi) < preview.getRadius() + pi.getRadius())
						placeable = false;
                }
                preview.setVelocity((aim.getPosition().getX() - preview.getPosition().getX()) / 100, (aim.getPosition().getY() - preview.getPosition().getY()) / 100);
                //bal eg�rgomb elenged�s�re preview m�solat�nak hozz�ad�sa a szimul�ci�hoz
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && placeable) {
                    preview.render_shape.setFillColor(sf::Color(255, 255, 255, 255));
                    space.push_back(preview);
                    charging = false;
                }
                //fel-le nyilakkal preview t�meg�nek v�ltoztat�sa
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
                    preview.setMass(preview.getMass() + 1000000000000);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    preview.setMass(preview.getMass() - 1000000000000);
                //C billenty�vel preview konstans �llapot�nak v�lt�sa
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                    preview.setIsConstant(!preview.getIsConstant());
                    preview.setVelocity(0, 0);
                    preview.setAcceleration(Vector(0, 0));
                }
                //eg�r g�rg�j�vel preview sugar�nak v�ltoztat�sa
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if(event.mouseWheelScroll.delta > 0)
						preview.setRadius(preview.getRadius() + 1);
					else
						preview.setRadius(preview.getRadius() - 1);
                }
                    
            }
            
        }

        //objektumok hely�nek friss�t�se
        UpdatePositions(space);

        //preview friss�t�se
        sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        preview.setPosition(Position(mouse_pos.x, mouse_pos.y));
        std::string isConstant = preview.getIsConstant() ? "true" : "false";
        preview_data = "Mass: " + std::to_string(preview.getMass()/10000000000000) + "*10^13 kg" +
            "\nRadius: " + std::to_string(preview.getRadius()) + " m" +
            "\nPosition: (" + std::to_string(preview.getPosition().getX()) + ", " + std::to_string(preview.getPosition().getY()) + ")" +
            "\nVelocity: " + std::to_string(preview.getVelocity().getMagnitude()) + " m/s (" + std::to_string(preview.getVelocity().getDirection().getX()) + ", " + std::to_string(preview.getVelocity().getDirection().getY()) + ")" +
            "\nIsConstant:" + isConstant;
        text.setString(preview_data);

        //vonal ami �sszek�ti a preview-t �s az aim-et
        line[0].position = sf::Vector2f(preview.getPosition().getX(), preview.getPosition().getY());
        line[1].position = sf::Vector2f(aim.getPosition().getX(), aim.getPosition().getY());

        //kirajzol�s
        window.clear();
        for (RenderPlanetaryObject& pi : space){
            window.draw(pi.render_shape);
        }
        if (charging){
            window.draw(aim.render_shape);
            window.draw(line, 2, sf::Lines);
            window.draw(text);
        }
        window.draw(preview.render_shape);
        window.display();
    }
}

#endif // GraphicRender