#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <iostream>

using namespace std;
sf::RectangleShape platform(sf::Vector2f(100,50));
int random1 = 300;
int random2 = 350;

enum {RightUp, RightRun, RightIdle, LeftUp, LeftRun, LeftIdle};

sf::Vector2i  source(1, RightUp);

const float gravity = 0.0001;
sf::Vector2f velocity(sf::Vector2f(0,0));

float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

int imageSize = 32;
float moveSpeed = 0.1;
float jumpSpeed = 0.2;
float groundHeight = 500;
string last = "R";
unsigned int windowWidth = 800.0f;
unsigned int windowHeight = 600.0f;

sf::Texture texture;
sf::Sprite playerImage;


void random() {
    std::random_device rd;     // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(10, 100); // Guaranteed unbiased
    random1 = uni(rng);
    random2 = uni(rng);
}

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
    // Initialisation
    sf::RectangleShape floor(sf::Vector2f(800,100));
    floor.setPosition(sf::Vector2f(0,500));
    floor.setFillColor(sf::Color(100, 200, 50));


    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dylan's Game");
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;

    if (!texture.loadFromFile("C:/Users/dylan/OneDrive - West Herts College/C Lion/HelloSFML/Spritesheet.png")) {

    }

    playerImage.setTexture(texture);

    playerImage.setPosition(0, 0);

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (playerImage.getPosition().y == groundHeight - 32 || (platform.getPosition().x < playerImage.getPosition().x < platform.getPosition().x + 200) && playerImage.getPosition().y == 318)) {
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
            if (source.x * imageSize >= texture.getSize().x)
                source.x = 0;
        }

        // Draw
        window.clear(sf::Color::Black); // Clear the window before drawing
        playerImage.setTextureRect(sf::IntRect(source.x * imageSize, source.y * imageSize, imageSize, imageSize));
        window.draw(playerImage);

        //random();
        platform.setPosition(sf::Vector2f((float) random1, (float) random2));
        platform.setFillColor(sf::Color(100, 250, 50));
        window.draw(platform);
        window.draw(floor);
        window.display();
    }

    return 0;
}
