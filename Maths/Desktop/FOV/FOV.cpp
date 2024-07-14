#include <SFML/Graphics.hpp>
#include <iostream>
#define PI (22/7.f)


void GetCircle(sf::ConvexShape& circle, float r, sf::Vector2f center, float angleRange)
{
    int pointsCount = circle.getPointCount();
    float deltaTheta = angleRange / (pointsCount - 1);
    float theta = -angleRange / 2;

    sf::Vector2f point;

    for (int i = 0; i < pointsCount - 1; i++)
    {

        point.x = center.x + r * cos(theta);
        point.y = center.y - r * sin(theta);

        circle.setPoint(i, point);
        theta += deltaTheta;
    }

    circle.setPoint(pointsCount - 1, center);
    circle.setOrigin(center);
    circle.setPosition(center);
}

float getMagnitude(sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "player");

    sf::CircleShape Player(25);
    Player.setPosition(400, 400);
    Player.setOrigin(25, 25);
    Player.setFillColor(sf::Color::Blue);
    sf::CircleShape circl(25.f);
    circl.setFillColor(sf::Color::Black);
    circl.setOrigin(25, 25);
    circl.setPosition(100, 100);
    float distance = 0;
    float detectionAngle = 0;
    sf::Vector2f center(400, 300);
    float dotProduct = 0;

    sf::ConvexShape cone(33);
    GetCircle(cone, 200, Player.getOrigin(), PI / 3);
    cone.setFillColor(sf::Color::Green);

    
    double horizontal = 0;
    double vertical = 0;
    float speed = 100;
    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;
    float angle = 0;
    float lookAtAngle;
    float detectAngle;
    sf::Vector2f direction;
    sf::Vector2f lookAtDirection;
    sf::Vector2f detectDirection;
    sf::Vector2f position = Player.getPosition();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            horizontal = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            horizontal = -1;
        }
        else
        {
            horizontal = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            vertical = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            vertical = 1;
        }
        else
        {
            vertical = 0;
        }

        if (vertical != 0 || horizontal != 0) {
            std::cout << distance << std::endl;
        }

        distance = sqrt(pow(circl.getPosition().x - cone.getPosition().x, 2) + pow(circl.getPosition().y - cone.getPosition().y, 2));
        detectionAngle = PI / 2;
        direction.x = horizontal;
        direction.y = vertical;


        position += deltaTime * speed * direction;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        lookAtDirection = (sf::Vector2f)mousePos - center;

        detectDirection = circl.getPosition() - Player.getPosition();

        detectAngle = atan2(detectDirection.y, detectDirection.x);

        lookAtAngle = atan2(lookAtDirection.y, lookAtDirection.x);


        dotProduct = detectDirection.x * lookAtDirection.x + detectDirection.y * lookAtDirection.y;

        float compareAngle = dotProduct / (getMagnitude(lookAtDirection) * getMagnitude(detectDirection));

        if (acos(compareAngle) <= PI / 5 && distance <= 220) {

            cone.setFillColor(sf::Color::Red);
        }
        else {
            cone.setFillColor(sf::Color::Green);
        }
        window.clear(sf::Color::White);
        cone.setRotation(lookAtAngle * 180 / PI);
        circl.setRotation(detectAngle * 180 / PI);
        Player.setPosition(position);
        cone.setPosition(position);
        window.draw(circl);
        window.draw(cone);
        window.draw(Player);

        window.display();
    }

    return 0;
}