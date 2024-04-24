#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <iostream>

// Vector

using namespace std;
enum {RightUp, RightRun, RightIdle, LeftUp, LeftRun, LeftIdle};

sf::Vector2i  source(1, RightUp);

const float gravity = 0.0004;
sf::Vector2f velocity(sf::Vector2f(0,0));

float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

int imageSize = 32;
float moveSpeed = 0.3;
float jumpSpeed = 0.4;
float groundHeight = 542;
string last = "R";
unsigned int windowWidth = 800.0f;
unsigned int windowHeight = 600.0f;
bool canJump;

sf::Texture texturePlayer;
sf::Sprite playerImage;

sf::Texture textureBackground;
sf::Sprite backgroundImage;

sf::Texture texturePlatform;
sf::Sprite platformImage;

std::random_device rd;     // Only used once to initialise (seed) engine
std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(300, 400); // Guaranteed unbiased
float random1 = uni(rng);
float random2 = uni(rng);

sf::RectangleShape platform(sf::Vector2f(100,50));





bool collision() {
    if (platform.getGlobalBounds().intersects(playerImage.getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    // Initialisation of platform
    platform.setPosition(sf::Vector2f(random1,random2));
    platform.setFillColor(sf::Color(100, 250, 50));

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dylan's Game");
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;

    if (!texturePlayer.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/Spritesheet.png")) {}
    playerImage.setTexture(texturePlayer);
    playerImage.setPosition(0, 0);

    if (!textureBackground.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/background.png")) {}
    backgroundImage.setTexture(textureBackground);
    backgroundImage.setPosition(0, 0);

    if (!texturePlatform.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/platform.png")) {}
    platformImage.setTexture(texturePlatform);
    platformImage.setPosition(sf::Vector2f(random1,random2));

    while (window.isOpen()) {
        // Update
        sf::Event Event{};
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            source.y = RightRun;
            last = "R";
            velocity.x = moveSpeed;
            if (collision() || playerImage.getPosition().x > 775) {
                velocity.x = 0;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            source.y = LeftRun;
            last = "L";
            velocity.x = -moveSpeed;
            if (collision() || playerImage.getPosition().x < -5) {
                velocity.x = 0;
            }


        } else {
            if (last == "L") {
                source.y = LeftIdle;
            } else {
                source.y = RightIdle;
            }
            velocity.x = 0;
        }

        // is the player on the ground?
        if (playerImage.getPosition().y == groundHeight - 32 || ((platform.getPosition().x < playerImage.getPosition().x < platform.getPosition().x + 200) && (playerImage.getPosition().y + 32 == platform.getPosition().y))) {
            canJump = true;
        } else {
            canJump = false;
        }
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump) {
            if (last == "R")
                source.y = RightUp;
            else
                source.y = LeftUp;

            velocity.y = -jumpSpeed;
        }


        if (collision()) {
            // Top of platform
            if (velocity.y > 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platform.getPosition().y - 32);
            }
                // Bottom of platform
            else if (velocity.y < 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platform.getPosition().y + platform.getSize().y);
            }
        }




        playerImage.move(velocity.x, velocity.y);

        if(playerImage.getPosition().y + 32 < groundHeight) {
            velocity.y += gravity;
            if (collision())
                velocity.y -= gravity;
        }
        else
            playerImage.setPosition(playerImage.getPosition().x, groundHeight - 32);




        frameCounter += frameSpeed * clock.restart().asSeconds();
        if (frameCounter >= switchFrame) {
            frameCounter = 0;
            source.x++;
            if (source.x * imageSize >= texturePlayer.getSize().x)
                source.x = 0;
        }

        // Draw
        window.clear(sf::Color::Black); // Clear the window before drawing
        playerImage.setTextureRect(sf::IntRect(source.x * imageSize, source.y * imageSize, imageSize, imageSize));
        window.draw(backgroundImage);
        window.draw(playerImage);
        window.draw(platformImage);

        window.display();
    }

    return 0;
}
