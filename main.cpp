#include <SFML/Graphics.hpp>


int main()
{
    //Initialisation
    float windowWidth = 800.0f;
    float windowHeight = 600.0f;

    float floorHeight = 100.0f;
    float floorWidth = 800.0f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dylan's Game");

    sf::RectangleShape floor(sf::Vector2f(floorWidth,floorHeight));
    floor.setFillColor(sf::Color(100,10,10));
    floor.setPosition(0.0f,windowHeight-floorHeight);

    while (window.isOpen()) {

        // Update
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Draw
        window.clear(sf::Color::Black);
        window.draw(floor);
        window.display();
    }


    return 0;
}