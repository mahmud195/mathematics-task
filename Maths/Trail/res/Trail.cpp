#include <SFML/Graphics.hpp>

sf::Vector2f LerpVector(sf::Vector2f a, sf::Vector2f b, float alpha) {
    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;
    return alpha * (b - a) + a;
}

struct CircleData {
    sf::CircleShape circle;
    float size;
    sf::Vector2f currentPosition;
    sf::Vector2f targetPosition;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Circles Follow");

    sf::Clock clock;

    CircleData firstCircle;
    firstCircle.size = 25.0f;
    firstCircle.circle.setRadius(firstCircle.size);
    firstCircle.circle.setFillColor(sf::Color::White);
    firstCircle.currentPosition = sf::Vector2f(400.0f, 300.0f);
    firstCircle.targetPosition = sf::Vector2f(400.0f, 300.0f);

    CircleData secondCircle;
    secondCircle.size = 22.0f;
    secondCircle.circle.setRadius(secondCircle.size);
    secondCircle.circle.setFillColor(sf::Color::White);
    secondCircle.currentPosition = sf::Vector2f(400.0f, 300.0f);
    secondCircle.targetPosition = sf::Vector2f(400.0f, 300.0f);

    CircleData thirdCircle;
    thirdCircle.size = 19.0f;
    thirdCircle.circle.setRadius(thirdCircle.size);
    thirdCircle.circle.setFillColor(sf::Color::White);
    thirdCircle.currentPosition = sf::Vector2f(400.0f, 300.0f);
    thirdCircle.targetPosition = sf::Vector2f(400.0f, 300.0f);

    CircleData fourCircle;
    fourCircle.size = 17.0f;
    fourCircle.circle.setRadius(fourCircle.size);
    fourCircle.circle.setFillColor(sf::Color::White);
    fourCircle.currentPosition = sf::Vector2f(400.0f, 300.0f);
    fourCircle.targetPosition = sf::Vector2f(400.0f, 300.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        firstCircle.targetPosition = mousePosition;

        float deltaTime = clock.restart().asSeconds();
        float lerpSpeed = 2.0f;

        firstCircle.currentPosition = LerpVector(firstCircle.currentPosition, firstCircle.targetPosition, lerpSpeed * deltaTime);
        firstCircle.circle.setPosition(firstCircle.currentPosition.x - firstCircle.size / 2, firstCircle.currentPosition.y - firstCircle.size / 2);
        window.draw(firstCircle.circle);

      

        secondCircle.targetPosition = firstCircle.currentPosition;
        secondCircle.currentPosition = LerpVector(secondCircle.currentPosition, secondCircle.targetPosition, lerpSpeed * deltaTime);
        secondCircle.circle.setPosition(secondCircle.currentPosition.x - secondCircle.size / 2, secondCircle.currentPosition.y - secondCircle.size / 2);
        window.draw(secondCircle.circle);

       

        thirdCircle.targetPosition = secondCircle.currentPosition;
        thirdCircle.currentPosition = LerpVector(thirdCircle.currentPosition, thirdCircle.targetPosition, lerpSpeed * deltaTime);
        thirdCircle.circle.setPosition(thirdCircle.currentPosition.x - thirdCircle.size / 2, thirdCircle.currentPosition.y - thirdCircle.size / 2);
        window.draw(thirdCircle.circle);

       

        fourCircle.targetPosition = thirdCircle.currentPosition;
        fourCircle.currentPosition = LerpVector(fourCircle.currentPosition, fourCircle.targetPosition, lerpSpeed * deltaTime);
        fourCircle.circle.setPosition(fourCircle.currentPosition.x - fourCircle.size / 2, fourCircle.currentPosition.y - fourCircle.size / 2);
        window.draw(fourCircle.circle);

        window.display();
    }

    return 0;
}
