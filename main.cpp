#include <SFML/Graphics.hpp>


float x = 10;
float y = 10;
float target_x;
float target_y;

void changeX() {
    if (target_x > x) {
        x++ ;
    } else if (target_x < x) {
        x-- ;
    } else {
        ;
    }
}

void changeY() {
    if (target_y > y) {
        y++ ;
    }
    if (target_y < y) {
        y-- ;
    }
    else {
        ;
    }
}




int main()
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Application");
    sf::CircleShape shape;



    shape.setRadius(20.f);

    shape.setFillColor(sf::Color::Cyan);



    while (window.isOpen())
    {
        sf::Event event{};
        target_x = sf::Mouse::getPosition(window).x - 20;
        target_y = sf::Mouse::getPosition(window).y - 20;

        changeX();
        changeY();



        shape.setPosition(x, y);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}