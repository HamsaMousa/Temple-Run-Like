#include "Gui.hpp"

// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the player scores text fields.
 *
 * Initializes text fields to display player scores on the GUI.
 * It sets position, font, character size and color for the text fields.
 */
void Gui::initPlayerScores()
{
    // Init points text for player 1
    pointsPlayer1.setPosition(sf::Vector2f(600.f, 25.f));
    pointsPlayer1.setFont(fonttextscore);
    pointsPlayer1.setCharacterSize(20);
    pointsPlayer1.setFillColor(sf::Color::White);

    // Init points text for player 2
    pointsPlayer2.setPosition(sf::Vector2f(600.f, 50.f));
    pointsPlayer2.setFont(fonttextscore);
    pointsPlayer2.setCharacterSize(20);
    pointsPlayer2.setFillColor(sf::Color::White);
}


/**
 * @brief Initializes the player lives.
 *
 * Initializes sprites to represent player lives on the GUI.
 * It sets texture, scale and position for the sprites.
 * Based on the number of lives, it creates a vector of sprites to display the 
 * certain number of lives.
 */
void Gui::initPlayerLives()
{
    for (int i = 0; i < this->maxnumberoflives ; ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(heartFullTexture);
        sprite.setScale(3.f, 3.f); // Adjust scale as needed
        
        sprite.setPosition(20.f + i * heartFullTexture.getSize().x * sprite.getScale().x, 20.f);
        player1Lives.push_back(sprite);

        sprite.setPosition(WINDOW_WIDTH - (this->maxnumberoflives - i) * heartFullTexture.getSize().x * sprite.getScale().x - 20.f, 
        /* heartFullTexture.getSize().y * sprite.getScale().y*/ 20.f);
        player2Lives.push_back(sprite);
    }
}

/**
 * @brief Initializes the game over text.
 *
 * Initializes text field to display 'GAME OVER' text on the GUI.
 * It sets font, character size, color, string and position for the text field.
 */
void Gui::initGameOverText()
{
    //gameOverText.setPosition(sf::Vector2f(400.f, 300.f));
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    
    gameOverText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, WINDOW_HEIGHT / 2.f - this->gameOverText.getGlobalBounds().height / 2.f));

}

// ----------------------------------------------------------
// Constructor / Destructor
// ----------------------------------------------------------
/**
 * @brief Constructs a new GUI object.
 *
 * Constructor for Gui object. It sets maximum number of lives,
 * loads font and textures
 * call initfunction to initialize player scores, player lives, and game over text.
 *
 * @param font The font used in GUI texts.
 * @param maxlifeset The maximum number of lives set for players.
 */
Gui::Gui(sf::Font& font,int maxlifeset) : font(font)  /*maxnumberoflives(5)*/
{

    maxnumberoflives = maxlifeset;

    std::string ipath = "assets/Oswald_DemiBold.ttf";
	if(!this->fonttextscore.loadFromFile(ipath))
	{
		throw("ERROR SettingState::initFonts COULD NOT LOAD FONT");
	}


    if (!heartFullTexture.loadFromFile("assets/heartfull.png") || !heartEmptyTexture.loadFromFile("assets/heartempty.png"))
    {
        std::cout << "ERROR::Gui::Failed to load heart textures" << std::endl;
    }

    initPlayerScores();
    initPlayerLives();
    initGameOverText();
}

/**
 * @brief Destroys the GUI object.
 * Nothing to destroy here
 */
Gui::~Gui() {}

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the player scores.
 *
 * Updates text fields to display current player scores on the GUI.
 *
 * @param player1Score The current score of player 1 that is given by the game state.
 * @param player2Score The current score of player 2 that is given by the game state.
 */
void Gui::updatePlayerScores(int player1Score, int player2Score)
{
    std::stringstream ss;
    ss << "Player 1 : " << player1Score;
    pointsPlayer1.setString(ss.str());

    ss.str(std::string());
    ss << "Player2 : " << player2Score;
    pointsPlayer2.setString(ss.str());
}


/**
 * @brief Updates the player lives.
 *
 * Updates sprites to represent current player lives on the GUI.
 * It sets texture for the sprites based on the number of lives if game state detected a collision
 * between a player and a obstacle it calls this function to update the GUI and render a heart empty texture.
 * 
 * @param player1LivesCount The current lives count of player 1 that is given by the game state.
 * @param player2LivesCount The current lives count of player 2 that is given by the game state.
 */
void Gui::updatePlayerLives(int player1LivesCount, int player2LivesCount)
{
    for (int i = 0; i < maxnumberoflives; ++i)
    {
        if (i >= player1LivesCount)
            player1Lives[i].setTexture(heartEmptyTexture);

        if (i >= player2LivesCount)
            player2Lives[i].setTexture(heartEmptyTexture);
    }
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the GUI.
 *
 * Renders player scores and player lives onto the provided render target.
 *
 * @param target The render target to which the GUI will be rendered.
 */
void Gui::render(sf::RenderTarget* target)
{
    target->draw(pointsPlayer1);
    target->draw(pointsPlayer2);

    for (auto& sprite : player1Lives)
        target->draw(sprite);

    for (auto& sprite : player2Lives)
        target->draw(sprite);
}

/**
 * @brief Renders the game over text.
 *
 * Renders 'GAME OVER' text onto the provided render target.
 *
 * @param target The render target to which the game over text will be rendered.
 */
void Gui::renderGameOver(sf::RenderTarget* target)
{
    target->draw(gameOverText);
}
