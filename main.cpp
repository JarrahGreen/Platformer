#include <SFML/Graphics.hpp>

int main()
{
    // Initialisation
    enum {RightUp, RightRun, RightIdle, LeftUp, LeftRun, LeftIdle};

    sf::Vector2i  source(1, RightUp);

    const float gravity = 0.0001;
    sf::Vector2f velocity(sf::Vector2f(0,0));

    float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

    int imageSize = 32;
    int idle;
    float moveSpeed = 0.1;
    float jumpSpeed = 0.1;
    float groundHeight = 500;

    unsigned int windowWidth = 800.0f;
    unsigned int windowHeight = 600.0f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dylan's Game");
    window.setKeyRepeatEnabled(false);

    sf::Texture texture;
    sf::Sprite playerImage;
    sf::Clock clock;

    if (!texture.loadFromFile("C:/Users/dylan/OneDrive - West Herts College/C Lion/HelloSFML/Spritesheet.png")) {

    }

    playerImage.setTexture(texture);

    playerImage.setPosition(0, 0);

    while (window.isOpen()) {
        // Update
        sf::Event Event{};
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            source.y = RightRun;
            velocity.x = moveSpeed;
            idle = 0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            source.y = LeftRun;
            velocity.x = -moveSpeed;
            idle = 1;
        }
        else
            velocity.x = 0;
            if (idle == 1)
                source.y = LeftIdle;
            else if (idle == 0)
                source.y = RightIdle;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerImage.getPosition().y == 468) {
            velocity.y = -jumpSpeed;
        }

        playerImage.move(velocity.x, velocity.y);

        if(playerImage.getPosition().y + 32 < groundHeight) {
            velocity.y += gravity;
        }
        else
            playerImage.setPosition(playerImage.getPosition().x, groundHeight - 32);

        frameCounter += frameSpeed * clock.restart().asSeconds();
        if (frameCounter >= switchFrame) {
            frameCounter = 0;
            source.x++;
            if (source.x * imageSize >= texture.getSize().x)
                source.x = 0;
        }

        // Draw
        playerImage.setTextureRect(sf::IntRect(source.x * imageSize, source.y * imageSize, imageSize, imageSize));
        window.draw(playerImage);
        window.display();
        window.clear(sf::Color::Black);
    }
    return 0;
}
