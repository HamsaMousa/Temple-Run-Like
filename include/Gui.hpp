#ifndef GUI_HPP
#define GUI_HPP


#include "GeneInc.hpp"
#include "GameStateConfig.hpp"

class Gui
{
private:
    sf::Font& font;
    sf::Text pointsPlayer1;
    sf::Text pointsPlayer2;
    sf::Text gameOverText;

    sf::Font fonttextscore;

    int maxnumberoflives = 5; //by default

    std::vector<sf::Sprite> player1Lives;
    std::vector<sf::Sprite> player2Lives;

    sf::Texture heartFullTexture;
    sf::Texture heartEmptyTexture;

public:
    Gui(sf::Font& font, int maxlifeset);
    ~Gui();

    void initPlayerScores();
    void initPlayerLives();
    void initGameOverText();
    void updatePlayerScores(int player1Score, int player2Score);
    void updatePlayerLives(int player1Lives, int player2Lives);
    void render(sf::RenderTarget* target);
    void renderGameOver(sf::RenderTarget* target);
};

#endif // GUI_HPP