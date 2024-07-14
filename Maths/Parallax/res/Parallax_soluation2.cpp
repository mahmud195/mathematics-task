
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 300), "SFML Template!");
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;

    float speeds[3] = { 100.f, 50.f, 30.f };

    sf::Sprite sprites[7];
    sf::Texture textures[4];

    for (int i = 0; i < 4; ++i) {
        textures[i].loadFromFile("background" + std::to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 7; ++i) {
        switch (i) {
        case 0:
            sprites[0].setTexture(textures[i]);
            break;
        case 1:
            sprites[1].setTexture(textures[i]);
            sprites[2].setTexture(textures[i]);
            break;
        case 2:
            sprites[3].setTexture(textures[i]);
            sprites[4].setTexture(textures[i]);
            break;
        case 3:
            sprites[5].setTexture(textures[i]);
            sprites[6].setTexture(textures[i]);
            break;
        default:
            break;
        }
        sprites[i].setTextureRect(sf::IntRect(10, 10, window.getSize().x, window.getSize().y));
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

        position.x += speeds[0] * deltaTime;
        position2.x += speeds[1] * deltaTime;
        position3.x += speeds[2] * deltaTime;


        window.clear();
        sprites[1].setPosition(-position3);
        sprites[2].setPosition((-position3.x + 600), position.y);
        sprites[3].setPosition(-position2.x, position.y);
        sprites[4].setPosition((-position2.x + 600), position.y);
        sprites[5].setPosition(-position.x, position.y);
        sprites[6].setPosition((-position.x + 600), position.y);
        for (int i = 0; i < 7; i++) {

            window.draw(sprites[i]);
        }

        window.display();
    }

    return 0;
}