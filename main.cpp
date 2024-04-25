#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
enum {RightUp, RightRun, RightIdle, LeftUp, LeftRun, LeftIdle};

sf::Vector2i  source(1, RightUp);

const float gravity = 0.0004;
sf::Vector2f velocity(sf::Vector2f(0,0));

float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

int imageSize = 32;
float moveSpeed = 0.3;
float jumpSpeed = 0.5;
float groundHeight = 900;
string last = "R";
unsigned int windowWidth = 1920;
unsigned int windowHeight = 1080;
bool canJump;

sf::Texture texturePlayer;
sf::Sprite playerImage;

sf::Texture textureBackground;
sf::Sprite backgroundImage;

sf::Texture texturePlatformOne;
sf::Sprite platformImageOne;

sf::Texture texturePlatformTwo;
sf::Sprite platformImageTwo;

sf::RectangleShape platformOne(sf::Vector2f(300, 120));
sf::RectangleShape platformTwo(sf::Vector2f(300, 120));

bool collisionOne() {
    if (platformOne.getGlobalBounds().intersects(playerImage.getGlobalBounds())) {
        return true;
    }
    else {return false;}
}

bool collisionTwo() {
    if (platformTwo.getGlobalBounds().intersects(playerImage.getGlobalBounds())) {
        return true;
    }
    else {return false;}
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Underwater Torture");
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;

    if (!texturePlayer.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/Spritesheet.png")) {}
    playerImage.setTexture(texturePlayer);
    playerImage.setPosition(0, 0);


    if (!textureBackground.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/background-good.png")) {}
    backgroundImage.setTexture(textureBackground);
    backgroundImage.setPosition(0, 0);


    platformOne.setPosition(sf::Vector2f(600, 700));
    if (!texturePlatformOne.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/platform.png")) {}
    platformImageOne.setTexture(texturePlatformOne);
    platformImageOne.setPosition(sf::Vector2f(600,700));


    platformTwo.setPosition(sf::Vector2f(900, 400));
    if (!texturePlatformTwo.loadFromFile("D:/Users/22000773/OneDrive - West Herts College/C Lion/HelloSFML/platform.png")) {}
    platformImageTwo.setTexture(texturePlatformTwo);
    platformImageTwo.setPosition(sf::Vector2f(900,400));





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
            if (collisionOne() || collisionTwo() || playerImage.getPosition().x > 1888) {
                velocity.x = 0;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            source.y = LeftRun;
            last = "L";
            velocity.x = -moveSpeed;
            if (collisionOne() || collisionTwo() || playerImage.getPosition().x < -5) {
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
        if (playerImage.getPosition().y == groundHeight - 32
        || ((platformOne.getPosition().x < playerImage.getPosition().x < platformOne.getPosition().x + 300)
        && (playerImage.getPosition().y + 32 == platformOne.getPosition().y))
        || ((platformTwo.getPosition().x < playerImage.getPosition().x < platformTwo.getPosition().x + 300)
        && (playerImage.getPosition().y + 32 == platformTwo.getPosition().y))) {
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


        if (collisionOne()) {
            // Top of platformOne
            if (velocity.y > 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platformOne.getPosition().y - 32);
            }
                // Bottom of platformOne
            else if (velocity.y < 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platformOne.getPosition().y + platformOne.getSize().y);
            }
        }

        if (collisionTwo()) {
            // Top of platformOne
            if (velocity.y > 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platformTwo.getPosition().y - 32);
            }
                // Bottom of platformOne
            else if (velocity.y < 0) {
                velocity.y = 0;
                playerImage.setPosition(playerImage.getPosition().x, platformTwo.getPosition().y + platformTwo.getSize().y);
            }
        }


        playerImage.move(velocity.x, velocity.y);

        if(playerImage.getPosition().y + 32 < groundHeight) {
            velocity.y += gravity;
            if (collisionOne() || collisionTwo())
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
        window.draw(platformImageOne);
        window.draw(platformImageTwo);


        window.display();
    }

    return 0;
}
