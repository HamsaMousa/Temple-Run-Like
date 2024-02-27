#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.hpp"
#include "Entity.hpp"
#include "Obstacle.hpp"

//TEST INIT WINDOW
TEST_CASE("Create window") {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Temple", sf::Style::Close | sf::Style::Titlebar);
    REQUIRE(window.isOpen());
}

//TEST INIT TEXTURES
//Test load background texture
TEST_CASE("Load background texture") {
    sf::Texture background;
    REQUIRE(background.loadFromFile("assets/gamestatebackground.png"));
}

//Test load player sheet
TEST_CASE("Load player texture") {
    sf::Texture player;
    REQUIRE(player.loadFromFile("assets/PLAYER_SHEET2.png"));
}

//Test load obstacle texture
TEST_CASE("Load obstacle texture") {
    sf::Texture obstacle;
    REQUIRE(obstacle.loadFromFile("assets/projetastev3.png"));
}

//Test load coin texture
TEST_CASE("Load coin texture") {
    sf::Texture coin;
    REQUIRE(coin.loadFromFile("assets/coin.png"));
}

//Test if player is created
TEST_CASE("Player is created") {
    sf::Texture playerTexture;
    playerTexture.loadFromFile("assets/PLAYER_SHEET2.png");
    int maxlifeset = 5;
    Player player(171.f, -100.f, playerTexture, maxlifeset);
    REQUIRE(player.getMovementSpeed() == 300.f);
}

//Test if obstacles are created
TEST_CASE("Obstacles are created") {
    sf::Texture obstacleTexture;
    obstacleTexture.loadFromFile("assets/projetastev3.png");
    Obstacle obstacle(171.f, -100.f, obstacleTexture, 1.f);
    REQUIRE(obstacle.getSpeed() == 1.f);
}

//Test if coins are created
TEST_CASE("Coins are created") {
    sf::Texture coinTexture;
    coinTexture.loadFromFile("assets/coin.png");
    Coin coin(171.f, -100.f, coinTexture, 1.f);
    REQUIRE(coin.getSpeed() == 1.f);
}

// Test case for obstacle deletion when out of screen
TEST_CASE("Obstacle deleted when out of screen") {
    // Create a window object (replace it with your actual window creation code)
    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), "Temple", sf::Style::Close | sf::Style::Titlebar);

    // Create an obstacle
    sf::Texture obstacleTexture;
    obstacleTexture.loadFromFile("assets/projetastev3.png");
    Obstacle obstacle(171.f, -100.f, obstacleTexture, 1.f);

    // Set the obstacle's position outside the screen
    sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();
    obstacle.setPosition(0.f, window.getSize().y + obstacleBounds.height);

    // Check that the obstacle's position is outside the screen
    sf::Vector2f obstaclePosition = obstacle.getPosition();
    REQUIRE(obstaclePosition.y > window.getSize().y);

    // Check that the obstacle is deleted
    obstacle.update(1.f);
    REQUIRE(obstaclePosition.y > window.getSize().y);
}

// Test case for coin deletion when out of screen
TEST_CASE("Coin deleted when out of screen") {
    // Create a window object (replace it with your actual window creation code)
    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), "Temple", sf::Style::Close | sf::Style::Titlebar);

    // Create a coin
    sf::Texture coinTexture;
    coinTexture.loadFromFile("assets/coin.png");
    Coin coin(171.f, -100.f, coinTexture, 1.f);

    // Set the coin's position outside the screen
    sf::FloatRect coinBounds = coin.getGlobalBounds();
    coin.setPosition(0.f, window.getSize().y + coinBounds.height);

    // Check that the coin's position is outside the screen
    sf::Vector2f coinPosition = coin.getPosition();
    REQUIRE(coinPosition.y > window.getSize().y);

    // Check that the coin is deleted
    coin.update(1.f);
    REQUIRE(coinPosition.y > window.getSize().y);
}