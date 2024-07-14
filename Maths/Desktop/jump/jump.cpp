#include <SFML/Graphics.hpp>

float Getjump(float time, float d)
{
    return (-4 / (d * d)) * time * time + (4 / d) * time;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "5oly ");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Clock clock;
    float time = 0;

    sf::Vector2f position(250, 300);

    sf::Vector2f startposition(250, 300);
    shape.setPosition(startposition);
    float d = 1;
    bool jumping = false;

    while (window.isOpen())
    {
        time = clock.getElapsedTime().asSeconds();

          clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumping == false) {
            clock.restart();
            jumping = true;

        }
        else if (position.y >=startposition.y && jumping == true )
        {
            jumping = false;
        }
       position.y = startposition.y - 250 * Getjump(time, d);
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

        }
        if (jumping == true)
        {
            shape.setPosition(position);
        }

        window.clear();
        
        window.draw(shape);
        window.display();
    }

    return 0;
}