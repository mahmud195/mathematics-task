#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265358979323846f

void GetCircle(sf::ConvexShape& circle, float r, sf::Vector2f center, float startAngle)
{
    int pointsCount = circle.getPointCount();
    float theta = startAngle;
    float deltaTheta = ((2 * PI) - (2 * startAngle)) / (pointsCount - 2);
    circle.setOrigin(center);
    sf::Vector2f point;

    for (int i = 0; i < pointsCount; i++)
    {
        point.x = center.x + r * cos(theta);
        point.y = center.y + r * sin(theta);

        circle.setPoint(i, point);
        theta += deltaTheta;
    }
    circle.setPoint(pointsCount - 1, center);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Professional Code");
    sf::ConvexShape shape(30);
    shape.setPosition(300, 200);
    shape.setFillColor(sf::Color::Green);

    float speed = 6;

    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;
    float startAngle = 0;

    while (window.isOpen())
    {
        float angle = (PI / 6) * fabs(sin(time * speed));
        float currentTime = clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - time;
        time = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            shape.setRotation(-180);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.setRotation(0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            shape.setRotation(-90);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            shape.setRotation(90);
        }

        GetCircle(shape, 75, sf::Vector2f(100, 100), angle);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
