#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159265f;

const sf::Vector2f PacmanCenter = sf::Vector2f(300.f, 200.f);

void GetCircle(sf::ConvexShape& circle, float r2, sf::Vector2f center, float startAngle)
{
    int pointsCount = circle.getPointCount();
    float theta = startAngle;
    float deltaTheta = ((2 * PI) - (2 * startAngle)) / (pointsCount - 2);
    circle.setOrigin(center);
    sf::Vector2f point;

    for (int i = 0; i < pointsCount; i++)
    {
        float r = r2;

        point.x = center.x + r * cos(theta);
        point.y = center.y + r * sin(theta);

        circle.setPoint(i, point);
        theta += deltaTheta;
    }
    circle.setPoint(pointsCount - 1, center);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "PacMan");
    sf::ConvexShape pacman(30);
    pacman.setPosition(PacmanCenter);
    pacman.setFillColor(sf::Color::Yellow);
    
    sf::CircleShape eye(20);
    eye.setOrigin(10, 10);
    eye.setPosition(PacmanCenter.x, PacmanCenter.y-80);
    eye.setFillColor(sf::Color::Black);

    float speed = 6;

    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;

    while (window.isOpen())
    {
        float angle = (PI / 7) * abs(sin(time * speed));
        float currentTime = clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - time;
        time = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pacman.setRotation(-180);
            eye.setPosition(PacmanCenter.x, PacmanCenter.y - 80);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pacman.setRotation(0);
            eye.setPosition(PacmanCenter.x, PacmanCenter.y - 80);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pacman.setRotation(-90);
            eye.setPosition(PacmanCenter.x-80, PacmanCenter.y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pacman.setRotation(90);
            eye.setPosition(PacmanCenter.x-80, PacmanCenter.y);
        }

        GetCircle(pacman, 150, sf::Vector2f(100, 100), angle);

        window.clear();
        window.draw(pacman);
        window.draw(eye);
        window.display();
    }

    return 0;
}
