#include <SFML/Graphics.hpp>


class ControlPoint
{
private:
    bool isDragging;

public:
    sf::CircleShape shape;

    sf::Vector2f GetPosition()
    {
        return shape.getPosition();
    }

    ControlPoint(sf::Vector2f position) {
        shape = sf::CircleShape(5);
        shape.setOrigin(5, 5);
        shape.setPosition(position);
    }

    void BeginDrag(sf::Vector2f mousePosition)
    {
        isDragging = shape.getGlobalBounds().contains(mousePosition);
    }

    void Drag(sf::Vector2f mousePosition)
    {
        if (!isDragging) return;

        shape.setPosition(mousePosition);
    }

    void EndDrag()
    {
        isDragging = false;
    }
};

float Lerp(float a, float b, float alpha)
{
    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;
    return alpha * (b - a) + a;
}

sf::Vector2f LerpVector(sf::Vector2f a, sf::Vector2f b, float alpha)
{
    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;
    return alpha * (b - a) + a;
}

sf::Color LerpColor(sf::Color a, sf::Color b, float alpha)
{
    sf::Color color;

    color.r = Lerp(a.r, b.r, alpha);
    color.g = Lerp(a.g, b.g, alpha);
    color.b = Lerp(a.b, b.b, alpha);

    return color;
}

void GetCurve(sf::VertexArray& curve, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
    float pointsCount = curve.getVertexCount();
    float deltaT = 1 / (pointsCount - 1);
    float t = 0;

    for (int i = 0; i < pointsCount; i++)
    {
        sf::Vector2f p12 = LerpVector(p1, p2, t);
        sf::Vector2f p13 = LerpVector(p2, p3, t);
        sf::Vector2f p14 = LerpVector(p3, p4, t);

        sf::Vector2f p20 = LerpVector(p12, p13, t);
        sf::Vector2f p21 = LerpVector(p13, p14, t);

        curve[i].position = LerpVector(p20, p21, t);
        curve[i].color = LerpColor(sf::Color::Cyan, sf::Color::White, t);

        t += deltaT;
    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML Template!");

    ControlPoint p1(sf::Vector2f(50, 350));
    ControlPoint p2(sf::Vector2f(50, 50));
    ControlPoint p3(sf::Vector2f(550, 50));
    ControlPoint p4(sf::Vector2f(550, 350));


    sf::VertexArray curve(sf::LineStrip, 30);

    sf::VertexArray lines(sf::LineStrip, 4);

    bool isDragging = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);

                p1.BeginDrag(mousePosition);
                p2.BeginDrag(mousePosition);
                p3.BeginDrag(mousePosition);
                p4.BeginDrag(mousePosition);


                isDragging = true;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                p1.EndDrag();
                p2.EndDrag();
                p3.EndDrag();
                p4.EndDrag();

                isDragging = false;
            }
        }

        if (isDragging)
        {
            sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
            p1.Drag(mousePosition);
            p2.Drag(mousePosition);
            p3.Drag(mousePosition);
            p4.Drag(mousePosition);
        }

        GetCurve(curve, p1.GetPosition(), p2.GetPosition(), p3.GetPosition(), p4.GetPosition());

        lines[0].position = p1.GetPosition();
        lines[1].position = p2.GetPosition();
        lines[2].position = p3.GetPosition();
        lines[3].position = p4.GetPosition();


        lines[0].color = sf::Color::White;
        lines[1].color = sf::Color::Magenta;
        lines[2].color = sf::Color::Red;
        lines[3].color = sf::Color::Cyan;

        window.clear();
        window.draw(curve);
        window.draw(lines);
        window.draw(p1.shape);
        window.draw(p2.shape);
        window.draw(p3.shape);
        window.draw(p4.shape);


        window.display();
    }

    return 0;
}