#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 300), "SFML Template!");
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;

    float speed = 70;
    float speed2 = 30;
    float speed3 = 15;

    sf::Sprite sprite[7];
    sf::Texture texture[4];

    texture[0].loadFromFile("background_1.png");
    texture[1].loadFromFile("background_2.png");
    texture[2].loadFromFile("background_3.png");
    texture[3].loadFromFile("background_4.png");

    for (int i = 0; i < 7; i++)
    {
        if (i == 0) {
            sprite[0].setTexture(texture[i]);
        }
        else if (i == 1) {
            sprite[1].setTexture(texture[i]);
            sprite[2].setTexture(texture[i]);
        }
        else if (i == 2) {
            sprite[3].setTexture(texture[i]);
            sprite[4].setTexture(texture[i]);

        }
        else if (i == 3)
        {
            sprite[5].setTexture(texture[i]);
            sprite[6].setTexture(texture[i]);
        }
        sprite[i].setTextureRect(sf::IntRect(10, 10, window.getSize().x, window.getSize().y));
    }

    sf::Vector2f position(0, 0);
    sf::Vector2f position2(0, 0);
    sf::Vector2f position3(0, 0);



    while (window.isOpen())
    {
        float currentTime = clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - time;
        time = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (position.x >= 600) {
            position.x = 0;
        }

        if (position2.x >= 600) {
            position2.x = 0;
        }
        if (position3.x >= 600) {
            position3.x = 0;
        }

        position.x += speed * deltaTime;
        position2.x += speed2 * deltaTime;
        position3.x += speed3 * deltaTime;


        window.clear();
        sprite[1].setPosition(-position3);
        sprite[2].setPosition((-position3.x + 600), position.y);
        sprite[3].setPosition(-position2.x, position.y);
        sprite[4].setPosition((-position2.x + 600), position.y);
        sprite[5].setPosition(-position.x, position.y);
        sprite[6].setPosition((-position.x + 600), position.y);
        for (int i = 0; i < 7; i++) {
          
            window.draw(sprite[i]);
        }

        window.display();
    }

    return 0;
}