#include <SFML/Graphics.hpp>


float x = 10;
float y = 10;
float target_x;
float target_y;
float speed = 1;

void changeX() {
    if (target_x > x) {
        x += speed ;
    } else if (target_x < x) {
        x-= speed ;
    } else {
        ;
    }
}

void changeY() {
    if (target_y > y) {
        y+= speed ;
    }
    if (target_y < y) {
        y-= speed ;
    }
    else {
        ;
    }
}

/*
bool checkHit() {
    if (((target_x - x < 5 && target_x - x > -1) || (target_x - x < 0 && target_x - x > -5))
    &&
    (target_y - y < 5 && target_y - y > -1) || (target_y - y < 0 && target_y - y > -5)) {
        return false;
    } else { return true; }
}
*/


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

        //window.clear();
        window.draw(shape);
        window.display();
    }
}