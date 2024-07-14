#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;

    RenderWindow window(VideoMode(1920, 1080), "SFML First Task", Style::Fullscreen);
    CircleShape shape(100.f);

    shape.setFillColor(Color(0, 0, 0));

    shape.setOrigin(shape.getRadius(), shape.getRadius());

    shape.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    RectangleShape squares[8];

    float radius = shape.getRadius();
    float rectWidth = 200.f;
    float rectHeight = 200.f;

    float angle = 0.f;

    for (int i = 0; i < 8; i++)
    {

        squares[i] = RectangleShape(Vector2f(rectWidth, rectHeight));

        squares[i].setOrigin(rectWidth / 2.f, rectHeight / 2.f);

        switch (i)
        {
        case 0: // Top-left corner
            squares[i].setPosition(480, 200);
            break;
        case 1: // Top center
            squares[i].setPosition(960, 200);
            break;
        case 2: // Top-right corner
            squares[i].setPosition(1500, 200);
            break;
        case 3: // Right center
            squares[i].setPosition(1500, 540);
            break;
        case 4: // Bottom-right corner
            squares[i].setPosition(1500, 880);
            break;
        case 5: // Bottom center
            squares[i].setPosition(960, 880);
            break;
        case 6: // Bottom-left corner
            squares[i].setPosition(480, 880);
            break;
        case 7: // Left edge
            squares[i].setPosition(480, 540);
            break;
        }

        squares[i].setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
    }

    while (window.isOpen())
    {

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            return 0;
        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(119, 119, 119));

        window.draw(shape);
        for (int i = 0; i < 8; i++)
        {
            window.draw(squares[i]);
        }

        Vector2i mousePosition = Mouse::getPosition(window);

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            for (int i = 0; i < 8; i++)
            {
                if (squares[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {

                    Color squareColor = squares[i].getFillColor();
                    shape.setFillColor(Color(squareColor));
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            shape.setFillColor(Color(0, 0, 0));
        }

        window.display();
    }

    return 0;
}
