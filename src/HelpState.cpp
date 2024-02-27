#include "HelpState.hpp"
// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initialize help screen variables, which includes player controls and game elements to help the user understand the game.
 * Loads textures for player controls and game elements.
 * Sets position, scale, font, character size and color for the text fields.
 */
void HelpState::initVariables()
{	
	//Initialize player 1 keys
	std::string player1KeysTexturePath = "assets/Player1Keys.png";
	if(!this->player1KeysTexture.loadFromFile(player1KeysTexturePath))
	{
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD KEYBOARD TEXTURE" << "\n";
	}

	this->player1Keys.setTexture(this->player1KeysTexture);
	this->player1Keys.setPosition(300.f, 30.f);
	this->player1Keys.setScale(0.5f, 0.5f);
	this->player1KeysText.setFont(this->font);
	this->player1KeysText.setCharacterSize(20);
	this->player1KeysText.setFillColor(sf::Color::White);
	this->player1KeysText.setPosition(330.f, 10.f);

	//Initialize player 2 keys
	std::string player2KeysTexturePath = "assets/Player2Keys.png";
	if(!this->player2KeysTexture.loadFromFile(player2KeysTexturePath))
	{
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD KEYBOARD TEXTURE" << "\n";
	}
	this->player2Keys.setTexture(this->player2KeysTexture);
	this->player2Keys.setPosition(830.f, 30.f);
	this->player2Keys.setScale(0.5f, 0.5f);
	this->player2KeysText.setFont(this->font);
	this->player2KeysText.setCharacterSize(20);
	this->player2KeysText.setFillColor(sf::Color::White);
	this->player2KeysText.setPosition(860.f, 10.f);
	
	// Initialize game elements text
	this->gameElementsText.setFont(this->font);
	this->gameElementsText.setCharacterSize(20);
	this->gameElementsText.setFillColor(sf::Color::White);
	this->gameElementsText.setPosition(610.f, 200.f);

	//Initialize players text and texture
	std::string playersTexturePath = "assets/singleplayer.png";
	if(!this->playersTexture.loadFromFile(playersTexturePath)){
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD PLAYERS TEXTURE" << "\n";
	}

	this->players.setTexture(this->playersTexture);
	this->players.setPosition(300.f, 260.f);
	this->playersText.setFont(this->font);
	this->playersText.setCharacterSize(20);
	this->playersText.setFillColor(sf::Color::White);
	this->playersText.setPosition(300.f, 350.f);

	//Initialize obstacles text and texture
	std::string obstaclesTexturePath = "assets/singleobstacle.png";
	if(!this->obstaclesTexture.loadFromFile(obstaclesTexturePath)){
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD OBSTACLES TEXTURE" << "\n";
	}

	this->obstacles.setTexture(this->obstaclesTexture);
	this->obstacles.setPosition(500.f, 240.f);
	this->obstacles.setScale(0.6f, 0.6f);
	this->obstaclesText.setFont(this->font);
	this->obstaclesText.setCharacterSize(20);
	this->obstaclesText.setFillColor(sf::Color::White);
	this->obstaclesText.setPosition(500.f, 350.f);

	//Initialize coins text and texture
	std::string coinsTexturePath = "assets/singlecoin.png";
	if(!this->coinsTexture.loadFromFile(coinsTexturePath)){
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD COINS TEXTURE" << "\n";
	}

	this->coins.setTexture(this->coinsTexture);
	this->coins.setPosition(690.f, 270.f);
	this->coins.setScale(4.0f, 4.0f);
	this->coinsText.setFont(this->font);
	this->coinsText.setCharacterSize(20);
	this->coinsText.setFillColor(sf::Color::White);
	this->coinsText.setPosition(700.f, 350.f);

	//Initialize the life text and texture
	std::string lifeTexturePath = "assets/heartfull.png";
	if(!this->lifeTexture.loadFromFile(lifeTexturePath)){
		std::cout << "ERROR HelpState::initVariables() COULD NOT LOAD WEAPONS TEXTURE" << "\n";
	}

	this->life.setTexture(this->lifeTexture);
	this->life.setPosition(880.f, 270.f);
	this->life.setScale(4.0f, 4.0f);
	this->lifeText.setFont(this->font);
	this->lifeText.setCharacterSize(20);
	this->lifeText.setFillColor(sf::Color::White);
	this->lifeText.setPosition(900.f, 350.f);


	// Initialize game instructions text
	this->gameInstructionstitleText.setFont(this->font);
	this->gameInstructionstitleText.setCharacterSize(20);
	this->gameInstructionstitleText.setFillColor(sf::Color::White);
	this->gameInstructionstitleText.setPosition(610.f, 400.f);
	this->gameInstructionsText.setFont(this->font);
	this->gameInstructionsText.setCharacterSize(20);
	this->gameInstructionsText.setFillColor(sf::Color::White);
	this->gameInstructionsText.setPosition(400.f, 430.f);
}

/**
 * @brief Initialize help screen background.
 * Loads background texture.
 */
void HelpState::initBackground()
{
	//std::cout << "HelpState::initBackground()" << "\n";

	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	std::string ipath="assets/templebackgrounddarker.jpg";
	//error gestion
	if(!this->backgroundTexture.loadFromFile(ipath))
	{
		std::cout << "ERROR HelpState::initBackground() COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->background.setTexture(&this->backgroundTexture);
}

/**
 * @brief Initialize fonts for the help screen.
 */
void HelpState::initFonts()
{
	//std::cout << "HelpState::initFonts()" << "\n";
	
	std::string ipath="assets/28_Days_Later.ttf";
	if(!this->font.loadFromFile(ipath))
	{
		throw("ERROR HelpState::initFonts COULD NOT LOAD FONT");
	}
}

/**
 * @brief Initialize keybinds for the help screen.
 * Opens the helpstate_keybinds.ini file and loads the keybinds.
 */
void HelpState::initKeybinds()
{

	//std::cout << "HelpState::initKeybinds()" << "\n";
	std::string ipath="resources/helpstate_keybinds.ini"; 
	std::ifstream ifs(ipath); 
	
	if(ifs.is_open())
	{
		std::cout << "Opened " + ipath + " file." << std::endl;
		std::string ikeybind = "";
		std::string ikey = "";
		while (ifs >> ikeybind >> ikey)
		{
			this->keybinds[ikeybind] = this->supportedKeys->at(ikey);
		}
	}
	else
	{
		std::cerr << "Cannot open" + ipath + " file." << std::endl;
	}
	ifs.close();
}

/**
 * @brief Initialize buttons for the help screen.
 * Here we create the back button to return to the main menu after reading the help screen.
 */
void HelpState::initButtons()
{
	// Create the back button
	this->buttons["BACK"] = new Button(10, 20, 150.f, 50.f,
		&this->font, "Back",30,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

}

// ----------------------------------------------------------
// Constructor/Destructor
// ----------------------------------------------------------
/**
 * @brief Construct a new HelpState object
 * Call the init functions.
 * 
 * @param window The current window of the game
 * @param supportedKeys Map of supported keys for input handling
 * @param states Stack of states for managing game states
 */
HelpState::HelpState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}


/**
 * @brief Destroy the HelpState object and release its resources.
 * Make sure to delete all the buttons.
 */
HelpState::~HelpState()
{
	
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second; //second because first is the key
	}
}


// ----------------------------------------------------------
// Update 
// ----------------------------------------------------------
/**
 * @brief Update input for the help screen.
 * Handle the closing of the help screen with the ESC key (in addition to the back button)
 * 
 * @param dt The time elapsed between the current frame and the previous frame
 */
void HelpState::updateInput(const float & dt)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

/**
 * @brief Update the buttons in the help screen.
 * Update button based on mouse position.
 * Verify if the back button is pressed and end the help screen if it is.
 */
void HelpState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// Back
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
}


/**
 * @brief Update the help text on the screen.
 * Update the text for the player keys, game elements and game instructions.
 */
void HelpState::updateText()
{
	// Update player keys text
	std::string player1Keys = "Player 1 Keys";
	std::string player2Keys = "Player 2 Keys";
	this->player1KeysText.setString(player1Keys);
	this->player2KeysText.setString(player2Keys);

	// Update game elements text
	std::string gameElements = "Game Elements";
	this->gameElementsText.setString(gameElements);
	std::string players = "players";
	this->playersText.setString(players);
	std::string obstacles = "obstacles";
	this->obstaclesText.setString(obstacles);
	std::string coins = "coins";
	this->coinsText.setString(coins);
	std::string lifee = "life";
	this->lifeText.setString(lifee);

	// Update game instructions text
	std::string gameInstructionsTitle = "Instructions";
	std::string gameInstructions = R"(
	Avoid obstacles and collect coins to increase your score.
	You can set the difficulty and the number of lives in the settings.
	)";

	this->gameInstructionstitleText.setString(gameInstructionsTitle);
	this->gameInstructionsText.setString(gameInstructions);
}

/**
 * @brief Update the HelpState screen.
 * Just call the update functions for the buttons and text.
 * 
 * @param dt The time elapsed between the current frame and the previous frame
 */
void HelpState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	// Update buttons
	this->updateButtons();

	// Update text
	this->updateText();
}


// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Render the buttons in the help screen.
 * 
 * @param target The render target to draw the buttons onto
 */
void HelpState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

}

/**
 * @brief Render the HelpState screen.
 * Render the background, buttons and text for the help screen.
 * 
 * @param target The render target to draw the HelpState screen onto
 */
void HelpState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	// Draw player keys text
	target->draw(this->player1KeysText);
	target->draw(this->player2KeysText);
	// Draw player keys
	target->draw(this->player1Keys);
	target->draw(this->player2Keys);

	// Draw game elements text
	target->draw(this->gameElementsText);
	target->draw(this->players);
	target->draw(this->playersText);
	target->draw(this->obstacles);
	target->draw(this->obstaclesText);
	target->draw(this->coins);
	target->draw(this->coinsText);
	target->draw(this->life);
	target->draw(this->lifeText);

	// Draw game instructions text
	target->draw(this->gameInstructionstitleText);
	target->draw(this->gameInstructionsText);

}
