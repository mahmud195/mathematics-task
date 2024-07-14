#include <SFML/Graphics.hpp>
#include <iostream>

#define PI (22 / 7.f)

float vectorMagnitude(float x, float y)
{
    float sum = x * x + y * y;
    return sqrt(sum);
}

float distanceToLine(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd)
{
    float A = lineEnd.y - lineStart.y;
    float B = lineStart.x - lineEnd.x;
    float C = lineEnd.x * lineStart.y - lineStart.x * lineEnd.y;

    float numerator = std::abs(A * point.x + B * point.y + C);
    float denominator = std::sqrt(A * A + B * B);

    return numerator / denominator;
}

void GetCircle(sf::ConvexShape& circle, float r, sf::Vector2f& center, float angleRange)
{
    int pointsCount = circle.getPointCount();
    float deltaTheta = angleRange / (pointsCount);
    float theta = -angleRange / 2;
    sf::Vector2f point;
    for (int i = 0; i < pointsCount; i++)
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

float GetMagnitude(sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void Normalize(sf::Vector2f& vector)
{
    float mag = GetMagnitude(vector);
    if (mag == 0)
        return;
    vector = (1 / mag) * vector;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1400), "TopDown!");
    sf::CircleShape player(20);
    player.setOrigin(17, 17);
    player.setPosition(300, 200);
    sf::CircleShape target(25);
    target.setOrigin(12.5, 12.5);
    target.setPosition(800, 700);
    target.setFillColor(sf::Color::Yellow);
    sf::Vector2f playerPostion = player.getPosition();
    player.setFillColor(sf::Color::Blue);
    sf::Vector2f center(300, 200);
    sf::ConvexShape cone(31);
    GetCircle(cone, 200, playerPostion, PI / 2);
    cone.setFillColor(sf::Color::Green);
    sf::Vector2f direction;
    double horizontal = 0;
    double vertical = 0;
    float speed = 75;
    sf::Clock clock;
    float time = 0;
    float deltaTime = 0;
    float angle = 0;
    sf::Vector2f position = player.getPosition();

    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = sf::Vector2f(position.x, position.y);
    line[1].position = sf::Vector2f(position.x + 200.f, position.y);
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

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
            if (horizontal < 1)
                horizontal += deltaTime;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (horizontal > -1)
                horizontal -= deltaTime;
        }
        else
        {
            if (horizontal > 10 * deltaTime)
                horizontal -= 10 * deltaTime;
            else if (horizontal < -10 * deltaTime)
                horizontal += 10 * deltaTime;
            else
                horizontal = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (vertical > -1)
                vertical -= deltaTime;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (vertical < 1)
                vertical += deltaTime;
        }
        else
        {
            if (vertical > 10 * deltaTime)
                vertical -= 10 * deltaTime;
            else if (vertical < -10 * deltaTime)
                vertical += 10 * deltaTime;
            else
                vertical = 0;
        }
        if (horizontal != 0 || vertical != 0)
        {
            direction.x = horizontal;
            direction.y = vertical;
            Normalize(direction);
            position += deltaTime * speed * direction;
        }

        sf::Vector2f lineEnd(line[1].position.x, line[1].position.y);
        float distToLine = distanceToLine(target.getPosition(), line[0].position, lineEnd);
        std::cout << "Distance to Line: " << distToLine << std::endl;

        window.clear(sf::Color::White);
        player.setPosition(position);

        sf::Vector2f conepos = cone.getPosition();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        angle = atan2(mousePos.y - conepos.y, mousePos.x - conepos.x) * 180 / PI;
        sf::Vector2f v1 = cone.getPosition() - target.getPosition();

        sf::Vector2f lineDirection(cos(angle * PI / 180.f), sin(angle * PI / 180.f));
        line[0].position = cone.getPosition();
        line[1].position = cone.getPosition() + 200.f * lineDirection;

        sf::Vector2f lineToCenter = cone.getPosition() - position;
        float angleToCenter = atan2(lineToCenter.y, lineToCenter.x) * 180 / PI;
        std::cout << "Angle between line and center: " << angleToCenter << std::endl;

        

        cone.setRotation(angle);
        cone.setPosition(player.getPosition());

        

        sf::Vector2f lineToTarget = target.getPosition() - cone.getPosition();
        float angleToTarget = atan2(lineToTarget.y, lineToTarget.x) * 180 / PI;
        float angleBetweenLineAndTarget = std::abs(angle - angleToTarget);
        std::cout << "Angle between line and target: " << angleBetweenLineAndTarget << std::endl;
        angleBetweenLineAndTarget = angleBetweenLineAndTarget *PI / 180.f;
        if (vectorMagnitude(v1.x, v1.y) < 207 && angleBetweenLineAndTarget <= PI/4)
        {
            cone.setFillColor(sf::Color::Red);
        }
        else
        {
            cone.setFillColor(sf::Color::Yellow);
        }
        window.draw(player);
        window.draw(target);
        window.draw(cone);
        window.display();
    }
    return 0;
}
