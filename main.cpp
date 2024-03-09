#include <SFML/Graphics.hpp>

int main()
{
    // Initialisation
    enum {Up, Left, Right};

    sf::Vector2i  source(1, Up);

    int imageSize = 32;

    unsigned int windowWidth = 800.0f;
    unsigned int windowHeight = 600.0f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dylan's Game");
    window.setKeyRepeatEnabled(false);

    sf::Texture texture;
    sf::Sprite playerImage;

    if (!texture.loadFromFile("C:/Users/dylan/OneDrive - West Herts College/C Lion/HelloSFML/test.png")) {

    }

    playerImage.setTexture(texture);

    // Set position of the playerImage sprite to the center of the window
    playerImage.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

    while (window.isOpen()) {
        // Update
        sf::Event Event{};
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (Event.key.code == sf::Keyboard::Up)
                        source.y = Up;
                    else if(Event.key.code == sf::Keyboard::Left)
                        source.y = Left;
                    else if(Event.key.code == sf::Keyboard::Right)
                        source.y = Right;
            }
        }

        source.x++;
        if (source.x * imageSize >= texture.getSize().x)
            source.x = 0;

        // Draw
        playerImage.setTextureRect(sf::IntRect(source.x * imageSize, source.y * imageSize, imageSize, imageSize));
        window.draw(playerImage);
        window.display();
        window.clear(sf::Color::Blue);
    }
    return 0;
}
