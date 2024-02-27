#include "SettingState.hpp"

// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the game background by loading a texture from the file.
 * Throws an error if the texture file can't be found or loaded.
 */
void SettingState::initBackground()
{
	//std::cout << "SettingState::initBackground()" << "\n";

	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	//std::string ipath="assets/templebackground.jpg";
	std::string ipath="assets/templebackgrounddarker.jpg";
	//error gestion
	if(!this->backgroundTexture.loadFromFile(ipath))
	{
		std::cout << "ERROR SettingState::initBackground() COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->background.setTexture(&this->backgroundTexture);
}

/**
 * @brief Loads fonts from file and initializes the sf::Font objects.
 * Throws an error if the font files can't be found or loaded.
 */
void SettingState::initFonts()
{
	//std::cout << "SettingState::initFonts()" << "\n";
	
	std::string ipath="assets/28_Days_Later.ttf";
	if(!this->font.loadFromFile(ipath))
	{
		throw("ERROR SettingState::initFonts COULD NOT LOAD FONT");
	}

	ipath = "assets/Oswald_DemiBold.ttf";
	if(!this->fonttext.loadFromFile(ipath))
	{
		throw("ERROR SettingState::initFonts COULD NOT LOAD FONT");
	}
}

/**
 * @brief Initializes game control key bindings by loading them from a file.
 * Stores the key bindings in the keybinds map.
 * Outputs an error message if the file can't be opened.
 * 
 * Here only keybind for settingstate is the close one aka esc.
 */
void SettingState::initKeybinds()
{

	//std::cout << "SettingState::initKeybinds()" << "\n";
	std::string ipath="resources/settingstate_keybinds.ini"; 
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
 * @brief Initializes game buttons and their properties including size, position, color, etc.
 * Also sets up the text that appears on the buttons.
 * Theses buttons will serve to change the game settings (lives, difficulty, etc).
 * 
 */
void SettingState::initButtons()
{

	//std::cout << "SettingState::initButtons()" << "\n";

	int buttonWidth = 250;
	int buttonHeight = 50;
	int buttonSpacing = 30;
	unsigned characterSize = 30;
	int screenWidth = this->window->getSize().x;
	int screenHeight = this->window->getSize().y;

	this->buttonPositions = calculateButtonPositions(screenWidth, screenHeight, buttonWidth, buttonHeight, 6, buttonSpacing);

	// for (size_t i = 0; i < buttonPositions.size(); ++i)
	// {
	// 	std::cout << "Button " << (i + 1) << " position: (" << buttonPositions[i].x << ", " << buttonPositions[i].y << ")\n";
	// }


	this->buttons["INC_LIVES"] = new Button(buttonPositions[0].x, buttonPositions[0].y, buttonWidth, buttonHeight,
		&this->font, "Increase Lives",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

	this->buttons["DEC_LIVES"] = new Button(buttonPositions[2].x, buttonPositions[2].y, buttonWidth, buttonHeight,
		&this->font, "Decrease Lives",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

	this->buttons["INC_DIFF"] = new Button(buttonPositions[3].x, buttonPositions[3].y, buttonWidth, buttonHeight,
		&this->font, "Increase Difficulty",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

	this->buttons["DEC_DIFF"] = new Button(buttonPositions[5].x, buttonPositions[5].y, buttonWidth, buttonHeight,
		&this->font, "Decrease Difficulty",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

	this->buttons["EXIT_STATE"] = new Button(10, 20, buttonWidth-100, buttonHeight,
		&this->font, "Back",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
	);

}


/**
 * @brief Calculates positions for game buttons, considering the total screen size.
 * Positions are calculated such that buttons are evenly distributed vertically.
 * Small utility function to be used in initButtons().
 * 
 * @param screenWidth Width of the game window
 * @param screenHeight Height of the game window
 * @param buttonWidth Width of a button
 * @param buttonHeight Height of a button
 * @param buttonCount Total number of buttons
 * @param spacing Vertical spacing between buttons
 * @return A vector of button positions
 */
std::vector<sf::Vector2f> SettingState::calculateButtonPositions(int screenWidth, int screenHeight, int buttonWidth, int buttonHeight, int buttonCount, int spacing)
{
	std::vector<sf::Vector2f> buttonPositions;

	int totalHeight = buttonCount * (buttonHeight + spacing) - spacing;
	int startY = (screenHeight - totalHeight) / 2;

	for (int i = 0; i < buttonCount; ++i)
	{
		float xPos = (screenWidth - buttonWidth) / 2;
		float yPos = startY + i * (buttonHeight + spacing);
		buttonPositions.push_back(sf::Vector2f(xPos, yPos));
	}

	return buttonPositions;
}

/**
 * @brief Initializes game text objects and sets their font, size, color, and position.
 * Aligns text horizontally center relative to the game window.
 * 
 * Basicly here to display the current settings changeable by the buttons, difficulty and lives for now.
 * 
 */
void SettingState::initText()
{
	// Initialize the text objects
	livesText.setFont(this->fonttext);
	livesText.setCharacterSize(40);
	livesText.setFillColor(sf::Color(200, 200, 200, 250));
	livesText.setPosition(600 , 215); //between button 1 and 2
	centerText(livesText, this->window->getSize().x);

	difficultyText.setFont(this->fonttext);
	difficultyText.setCharacterSize(40);
	difficultyText.setFillColor(sf::Color(200, 200, 200, 250));
	difficultyText.setPosition(600, 455); //betwenn button 4 and 5
	centerText(difficultyText, this->window->getSize().x);

}

/**
 * @brief Adjusts the horizontal position of the given sf::Text object so that it is centered relative to the screen width.
 * Small utility function to be used in initText().
 * 
 * @param text Text object to be centered
 * @param screenWidth Width of the game window
 */
void SettingState::centerText(sf::Text& text, int screenWidth) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
	float xPos = screenWidth / 2.0f;
	text.setPosition(xPos, text.getPosition().y);
}



// ----------------------------------------------------------
// Constructor/Destructor
// ----------------------------------------------------------
/**
 * @brief Constructs a new SettingState.
 * Initializes the settings by calling initmethods
 * 
 * Use a pointer to the gamestateconfig to be able to change the settings to later use them in the game.
 * 
 * @param window Pointer to the game window
 * @param supportedKeys Pointer to the map of supported keys
 * @param states Pointer to the stack of states
 * @param config Pointer to the GameStateConfig
 */
SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,GameStateConfig* config)
	: State(window, supportedKeys, states), config(config)
{
	this->initText();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

/**
 * @brief Destroys the SettingState object.
 * Here Deletes all dynamically allocated buttons.
 */
SettingState::~SettingState()
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
 * @brief Processes input for the state.
 * Here, if the 'CLOSE' key is pressed, the state ends. (in addition to the usual quit with the button)
 * @param dt Time interval to update the state for
 */
void SettingState::updateInput(const float & dt)
{
	//Quit the setting with echap
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

/**
 * @brief Updates all the buttons in the state.
 * Detects button press events and performs relevant actions:
 * - "INC_LIVES" and "DEC_LIVES" buttons modify the number of lives
 * - "INC_DIFF" and "DEC_DIFF" buttons modify the difficulty level
 * - "EXIT_STATE" button ends the state
 */
void SettingState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// Increase number of lives
	if (this->buttons["INC_LIVES"]->isPressed())
	{
		// Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
		this->config->numberlives++;
		if(this->config->numberlives > 8)
			this->config->numberlives = 8;
	}

	// Decrease number of lives
	if (this->buttons["DEC_LIVES"]->isPressed())
	{
		// Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
		if (this->config->numberlives > 1)
		{
			this->config->numberlives--;
		}
	}

	// Increase difficulty
	if (this->buttons["INC_DIFF"]->isPressed())
	{
		// Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
		this->config->difficulty += 0.1f;
		if(this->config->difficulty > 4.5f)
		{
			this->config->difficulty = 4.5f;
		}
	}

	// Decrease difficulty
	if (this->buttons["DEC_DIFF"]->isPressed())
	{
		// Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
		if (this->config->difficulty > 1.0f)
		{
			this->config->difficulty -= 0.1f;
		}
	}

	//Quit the setting state when button clicked
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		//Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
		
		this->endState();
	}
}

/**
 * @brief Updates the state bu calling other updates methods.
 * Reprint the text related to lives and difficulty based on the current settings changed by the buttons.
 * @param dt Time interval to update the state for
 */
void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

	// Update the lives text string
	std::string livesStr = "" + std::to_string(this->config->numberlives);
	if (this->config->numberlives <= 1) {
		livesStr += " (min)";
	}
	if (this->config->numberlives >= 8) {
		livesStr += " (max)";
	}
	livesText.setString(livesStr);
	centerText(livesText, this->window->getSize().x);

	// Update the difficulty text string
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << this->config->difficulty;
	std::string difficultyStr = "" + stream.str();
	if (this->config->difficulty <= 1.0f) {
		difficultyStr += " (min)";
	}
	if (this->config->difficulty >= 4.5f) {
		difficultyStr += " (max)";
	}
	difficultyText.setString(difficultyStr);
	centerText(difficultyText, this->window->getSize().x);

}


// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders all buttons of the state to the target.
 * @param target Render target to which buttons will be drawn
 */
void SettingState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}


/**
 * @brief Renders the state to the target, which includes the background, buttons, and text.
 * If no target is specified, the state is rendered to the game window.
 * @param target Render target to which the state will be drawn
 */
void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	
	this->renderButtons(*target);

	// Render the text
	target->draw(this->livesText);
	target->draw(this->difficultyText);
}
