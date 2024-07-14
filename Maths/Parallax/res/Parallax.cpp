#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(550, 272), "Parallax Background");

    // Load textures
    sf::Texture background1Texture, background2Texture, background3Texture, background4Texture;

    if (!background1Texture.loadFromFile("background1.png") ||
        !background2Texture.loadFromFile("background2.png") ||
        !background3Texture.loadFromFile("background3.png") ||
        !background4Texture.loadFromFile("background4.png")) {
        return EXIT_FAILURE;
    }

    sf::Sprite background1(background1Texture);
    sf::Sprite background2(background2Texture);
    sf::Sprite background3(background3Texture);
    sf::Sprite background4(background4Texture);
    sf::Sprite background6(background2Texture);
    sf::Sprite background7(background3Texture);
    sf::Sprite background8(background4Texture);

    // Set initial positions
    background1.setPosition(0, 0);
    background2.setPosition(0, 0);
    background3.setPosition(0, 0);
    background4.setPosition(0, 0);
    background6.setPosition(background2Texture.getSize().x, 0);
    background7.setPosition(background3Texture.getSize().x, 0);
    background8.setPosition(background4Texture.getSize().x, 0);

    float background1Speed = -40.f;
    float background2Speed = -25.f;
    float background3Speed = -20.0f;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        background2.move(sf::Vector2f(background1Speed * deltaTime, 0.0f));
        background3.move(sf::Vector2f(background2Speed * deltaTime, 0.0f));
        background4.move(sf::Vector2f(background3Speed * deltaTime, 0.0f));
        background6.move(sf::Vector2f(background1Speed * deltaTime, 0.0f));
        background7.move(sf::Vector2f(background2Speed * deltaTime, 0.0f));
        background8.move(sf::Vector2f(background3Speed * deltaTime, 0.0f));

        if(background2.getPosition().x == 0)
          background6.setPosition(background2Texture.getSize().x , 0);

        if (background6.getPosition().x == 0)
            background2.setPosition(background2Texture.getSize().x , 0);

        if (background7.getPosition().x == 0)
            background3.setPosition(background3Texture.getSize().x, 0);

        if (background3.getPosition().x == 0)
            background7.setPosition(background3Texture.getSize().x, 0);

        if (background4.getPosition().x == 0)
            background8.setPosition(background4Texture.getSize().x, 0);

        if (background8.getPosition().x == 0)
            background4.setPosition(background4Texture.getSize().x, 0);




        window.clear();

        // Draw the textures
        window.draw(background1);
        window.draw(background2);
        window.draw(background6);
        window.draw(background3);
        window.draw(background7);
        window.draw(background4);
        window.draw(background8);

        window.display();
    }

    return EXIT_SUCCESS;
}
