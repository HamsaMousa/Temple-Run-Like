#include "MainMenuState.hpp"

// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/** 
 * @brief Initializer variable for MainMenuState
 * Nothing to do here for now
 */
void MainMenuState::initVariables()
{
    //std::cout << "MainMenuState::initVariables()" << "\n";
}

/** 
 * @brief Initialize the background of the MainMenuState
 *
 * Loads a texture from a file, sets it as the background of the MainMenuState and creates an overlay
 */
void MainMenuState::initBackground()
{
    //std::cout << "MainMenuState::initBackground()" << "\n";
    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)
    ));

    //std::string ipath="assets/v2background.png";
    std::string ipath="assets/templebackground.jpg";
    //error gestion
    if(!this->backgroundTexture.loadFromFile(ipath))
    {
        std::cout << "ERROR MainMenuState::initBackground() COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
    }

    this->background.setTexture(&this->backgroundTexture);

    // Set up the transparent overlay
    sf::RectangleShape overlay(this->background.getSize());
    overlay.setFillColor(sf::Color(0, 0, 0, 140)); // Half transparent black

    this->overlay = overlay; // assuming 'overlay' is a member of MainMenuState
}

/** 
 * @brief Initialize the fonts for the MainMenuState
 *
 * Loads a font from a file.
 */
void MainMenuState::initFonts()
{
    //std::cout << "MainMenuState::initFonts()" << "\n";
    
    std::string ipath="assets/28_Days_Later.ttf";
    if(!this->font.loadFromFile(ipath))
    {
        throw("ERROR MainMenuState::initFonts COULD NOT LOAD FONT");
    }
}

/** 
 * @brief Initialize the keybinds for the MainMenuState
 * Open file mainmenustate_initkeybinds.ini and read the keybinds from it.
 */

void MainMenuState::initKeybinds()
{   
    //std::cout << "MainMenuState::initKeybinds()" << "\n";
	std::string ipath="resources/mainmenustate_initkeybinds.ini"; 
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
 * @brief Initialize the buttons for the MainMenuState
 * Create buttons and set their position, size and color.
 */
void MainMenuState::initButtons()
{
    //std::cout << "MainMenuState::initButtons()" << "\n";

    int buttonWidth = 200;
    int buttonHeight = 60;
    int buttonSpacing = 40;
    unsigned characterSize = 40;
    int screenWidth = this->window->getSize().x;
    int screenHeight = this->window->getSize().y;

    std::vector<sf::Vector2f> buttonPositions = calculateButtonPositions(screenWidth, screenHeight, buttonWidth, buttonHeight, 4, buttonSpacing);

    this->buttons["GAME_STATE"] = new Button(buttonPositions[0].x, buttonPositions[0].y, buttonWidth, buttonHeight,
        &this->font, "New Game",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
    );

    this->buttons["SETTING_STATE"] = new Button(buttonPositions[1].x, buttonPositions[1].y, buttonWidth, buttonHeight,
        &this->font, "Setting",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
    );

    this->buttons["HELP_STATE"] = new Button(buttonPositions[2].x, buttonPositions[2].y, buttonWidth, buttonHeight,
        &this->font, "Help",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
    );

    this->buttons["EXIT_STATE"] = new Button(buttonPositions[3].x, buttonPositions[3].y, buttonWidth, buttonHeight,
        &this->font, "Quit",characterSize,
		sf::Color(200, 200, 200, 250), sf::Color::White,sf::Color::White,
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50)
    );
}

/** 
 * @brief Calculate the positions for the buttons
 * Utility function for initButtons()
 * Calculate the position of each button based on screen size, button size and spacing.
 *
 * @param screenWidth Width of the screen
 * @param screenHeight Height of the screen
 * @param buttonWidth Width of a button
 * @param buttonHeight Height of a button
 * @param buttonCount Number of buttons
 * @param spacing Spacing between buttons
 * 
 * @return vector of positions for the buttons
 */
std::vector<sf::Vector2f> MainMenuState::calculateButtonPositions(int screenWidth, int screenHeight, int buttonWidth, int buttonHeight, int buttonCount, int spacing)
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

// ----------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------
/** 
 * @brief Constructors/Destructors
 *
 * Create a new instance of MainMenuState. 
 * Use the parent constructor to initialize the window, supportedKeys and states and link the configgamestate to then give it to the gamestate.
 */
MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,GameStateConfig* config)
    : State(window,supportedKeys,states),config(config) 
{
    //std::cout << "MainMenuState::MainMenuState()" << "\n";
    this->initVariables(); 
    this->initBackground();
    this->initFonts(); 
    this->initKeybinds();
    this->initButtons(); 

}   

/** 
 * @brief Destructor
 *
 * Destroy the MainMenuState, here the buttons.
 */

MainMenuState::~MainMenuState()
{

    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second; //second because first is the key
    }

    //delete this->config;
}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Returns the mouse position as a SFML Text object.
 *
 * The function loads a font file, and sets the text string to the current mouse position.
 * Mostly for debugging purposes.
 * @return sf::Text object representing the current mouse position.
 */
sf::Text MainMenuState::retmousepos()
{
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
    
    //load font2
    std::string ipath="assets/Oswald_DemiBold.ttf";
    if(!this->font2.loadFromFile(ipath))
    {
        throw("ERROR MainMenuState::retmousepos COULD NOT LOAD FONT");
    }
    mouseText.setFont(this->font2);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << "(" << this->mousePosView.x << ";" << this->mousePosView.y << ")";
    mouseText.setString(ss.str());

    return mouseText;
}

/*
void MainMenuState::endState()
{
    std::cout << "Ending MainMenuState!" << "\n";
}
*/

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/** 
 * @brief Update input in the main menu state
 * Now defined in the father State.hpp directly
 * @param dt Delta time
 */
void MainMenuState::updateInput(const float& dt)
{
    //this->checkForQuit(); //cf. defined in the father State.hpp
}

/**
 * @brief Updates the state of the buttons in the main menu.
 *
 * The function iterates over all the buttons in the main menu and checks if they have been pressed. If a button has been pressed, the appropriate action is taken.
 * Here we have 3 buttons: New Game, Settings and Quit.
 * So if the New Game button is pressed, we push a new GameState onto the stack of states, to play the game for example.
 */
void MainMenuState::updateButtons()
{
    //update all the buttons in the state and handles their functionality
    for (auto &it : this->buttons)
    {
        //&it so it's a reference avoid making a copy of the element 
        //we work directly with the original data
        it.second->update(this->mousePosView);
    }

    //New Game
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        //we have access to the stack of states
        this->states->push(new GameState(this->window, this->supportedKeys,this->states,this->config));
    }

    //Quit the game
    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        //if this->endstate=true; //Game.cpp will quit the game because checkForQuit() will be true
        this->endState();
    }

    //Settings 
    if (this->buttons["SETTING_STATE"]->isPressed())
    {
        // Add delay
		sf::sleep(sf::milliseconds(250)); // 250 milliseconds = 0.25 seconds
        this->states->push(new SettingState(this->window, this->supportedKeys,this->states,this->config));
    }

    if (this->buttons["HELP_STATE"]->isPressed())
    {
        this->states->push(new HelpState(this->window, this->supportedKeys,this->states));
    }

}

/**
 * @brief Updates the state of the main menu.
 *
 * The function call init funtionc to updates the mouse positions, checks for input, and updates the buttons.
 *
 * @param dt The time passed since the last frame.
 */
void MainMenuState::update(const float& dt)
{
    // // Declare and initialize the static variable
    // static bool name_printed = false; //static so it's not reinitialized at each call
    // // Print the method name only once
    // if (!name_printed)
    // {
    //     std::cout << "1st MainMenuState::update()" << "\n";
    //     name_printed = true;
    //     std::cout << "..." << "\n";
    // }


    this->updateMousePositions(); //herited from State.hpp
    this->updateInput(dt);
    //now we have a map of buttons
    this->updateButtons();
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the buttons in the main menu.
 *
 * The function iterates over all the buttons in the main menu and renders them to the given render target.
 *
 * @param target The render target to draw to.
 */
void MainMenuState::renderButtons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
    {
        //same cf. updateButtons()
        it.second->render(target);

    }
}

/**
 * @brief Renders the main menu.
 *
 * The function draws the background and call function to also render the buttons
 *
 * @param target The render target to draw to. If this is null, the window is used as the target.
 */

void MainMenuState::render(sf::RenderTarget *target) 
{
    if (!target)
		target = this->window;

    target->draw(this->background);
    this->window->draw(this->overlay);

    //now we have a map of buttons
    this->renderButtons(*target);

    //debug
    //target->draw(this->retmousepos());
}
