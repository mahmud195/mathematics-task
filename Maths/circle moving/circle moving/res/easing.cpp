#include <SFML/Graphics.hpp>
#include "bounce.h"
#include "Back.h"
#include "Circ.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML Template!");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);

    shape.setOrigin(25, 25);

    sf::Vector2f targetPosition;

    sf::Vector2f position;
    sf::Vector2f startPosition;

    sf::Clock clock;

    float time = 0;

    float d = 2;

    bool isMoving = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                targetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                clock.restart();
                startPosition = shape.getPosition();
                isMoving = true;
            }

        }

        time = clock.getElapsedTime().asSeconds();

        if (isMoving)
        {
            //position.x = Bounce::easeInOut(time, startPosition.x, targetPosition.x - startPosition.x, d);
            //position.y = Bounce::easeInOut(time, startPosition.y, targetPosition.y - startPosition.y, d);
            
            
            //position.x = Circ::easeInOut(time, startPosition.x, targetPosition.x - startPosition.x, d);
            //position.y = Circ::easeInOut(time, startPosition.y, targetPosition.y - startPosition.y, d);

            position.x = Back::easeOut(time, startPosition.x, targetPosition.x - startPosition.x, d);
            position.y = Back::easeOut(time, startPosition.y, targetPosition.y - startPosition.y, d);


            if (time > d)
            {
                isMoving = false;
            }

        }
        window.clear();
        shape.setPosition(position);
        window.draw(shape);
        window.display();
    }

    return 0;
}
