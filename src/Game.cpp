#include "Game.hpp"

// ----------------------------------------------------------
// initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the game variables.
 * Window, fullscreen, dt, etc.
 */
void Game::initVariables() 
{
	this->window=nullptr;
	this->fullscreen=false;
	this->dt=0.f;
}

/**
 * @brief Initializes the game window.
 * Creates a SFML window using options determined
 */
void Game::initWindow()
{
	//std::cout << "Game::initWindow()" << "\n";
	
	std::string title = "Temple"; //default
	
	sf::VideoMode window_bounds(1280,720);
	//sf::VideoMode window_bounds(sf::VideoMode::getDesktopMode()); //todo
	
	this->fullscreen = false; //default 

	unsigned framerate_limit = 120; //default
	bool vertical_sync_enabled = false; //default


	if(this->fullscreen)
	{
		this->window=new sf::RenderWindow(window_bounds,title, sf::Style::Fullscreen); 
	}
	else 
	{	//(this->fullscreen==false
		this->window=new sf::RenderWindow(window_bounds,title, sf::Style::Close | sf::Style::Titlebar /*| sf::Style::Resize*/); 
	}

	this->window->setFramerateLimit(framerate_limit);			
	this->window->setVerticalSyncEnabled(vertical_sync_enabled); 	

}

/**
 * @brief Initializes the supported keys.
 * Reads the file game_initkeys.ini and fills the map supportedKeys.
 * It will allow to use the keys in the game.
 */
void Game::initKeys()
{	

	//std::cout << "Game::initKeys()" << "\n";
		
	std::string ipath="resources/game_initkeys.ini";
	std::ifstream ifs(ipath); 
	//VOIR LE CMAKE QUI COPIE RESOURCES DANS LE BUILD ET LA OK
    if(ifs.is_open())
    {
		std::cout << "Opened " + ipath + " file." << std::endl;
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }
    else
    {
		std::cerr << "Cannot open" + ipath + " file." << std::endl;
    }
    ifs.close();
	
    //debug
    // for(auto i : this->supportedKeys)
    // {
    //     std::cout << i.first << " " << i.second << "\n";
    // }
	
}

/**
 * @brief Initializes the game states.
 * Pushes the MainMenuState to the stack of states.
 * The stack of states will be used to manage the game states.
 */
void Game::initStates()
{

	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states, this->config)); 
	//&this->states = pointer to the original stack of states (in Game.hpp)

}

// ----------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------
/**
 * @brief Returns the singleton instance of the game.
 *
 * @return The singleton instance of the game.
 */
Game& Game::getInstance()
{
    static Game self;
    return self;
}

/**
 * @brief Constructs a new Game object.
 * Initializes the game variables.
 * Initializes the supported keys.
 * Initializes the game states.
 * Also create a gamestateconfig object that will be used to store some parameters of the game (life, difficulty, etc.)
 */
Game::Game()
{	
	this->config = new GameStateConfig();
	
	this->initWindow();
	this->initKeys(); //avant de faire initStates() car on a besoin de this->supportedKeys
	this->initStates();
	
}

/**
 * @brief Destroys the Game object.
 * Checks if states is not empty and deletes the states.
 */
Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top(); //remove data of the top state pointer
		this->states.pop(); //remove the top state pointer
	}

	//delete this->config; //pas besoin car singleton
	
}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Ends the application.
 * Nothing really special here, just a message.
 */
void Game::endApplication()
{
	//system("clear");
	std::cout << R"(
    _      _     _            _        _     _ 
   / \    | |__ (_) ___ _ __ | |_ ___ | |_  | |
  / _ \   | '_ \| |/ _ \ '_ \| __/ _ \| __| | |
 / ___ \  | |_) | |  __/ | | | || (_) | |_  |_|
/_/   \_\ |_.__/|_|\___|_| |_|\__\___/ \__| (_)
                                               
	)" << "\n";

	std::cout << R"(
 ____             _ _               _     _   _                           
| __ )  ___ _ __ (_) |_ ___     ___| |_  | | | | __ _ _ __ ___  ___  __ _ 
|  _ \ / _ \ '_ \| | __/ _ \   / _ \ __| | |_| |/ _` | '_ ` _ \/ __|/ _` |
| |_) |  __/ | | | | || (_) | |  __/ |_  |  _  | (_| | | | | | \__ \ (_| |
|____/ \___|_| |_|_|\__\___/   \___|\__| |_| |_|\__,_|_| |_| |_|___/\__,_|                                                           
	)" << "\n";

}


// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the time delta.
 * Very important function to update the dt variable with the time it takes to update and render one frame.
 * It will be used to move the game objects in a consistent manner.
 */
void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/
	this->dt = this->dtClock.restart().asSeconds(); 
	//std::cout << this->dt << "\n";
}

/**
 * @brief Updates the SFML events.
 * Polls the SFML events.
 * If the window is closed, it ends the application.
 */
void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->sfEvent)) //pollevent to be able to press buttons
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

/**
 * @brief Updates the game.
 * Updates the SFML events.
 * If the states stack is not empty, it updates the top state.
 * If the top state is quit, it removes the top state.
 * If the states stack is empty, it ends the application.
 */
void Game::update()
{

	this->updateSFMLEvents();

	if (!this->states.empty()) 
	{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				//std::cout << "Game::update() this->states.top()->getQuit()=true" << "\n";
				//std::cout << "this->states.size = " << this->states.size() << "\n";

				// We have different State subclasses, e.g., MenuState, GameState, etc.
				if (auto menuState = dynamic_cast<MainMenuState*>(this->states.top())) {
					std::cout << "Quitting state of type: " << typeid(*menuState).name() << "\n";
				} 
				else if (auto gameState = dynamic_cast<GameState*>(this->states.top())) {
					std::cout << "Quitting state of type: " << typeid(*gameState).name() << "\n";
				}
				else if (auto gameState = dynamic_cast<SettingState*>(this->states.top())) {
					std::cout << "Quitting state of type: " << typeid(*gameState).name() << "\n";
				}

				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
				//std::cout << "this->states.size = " << this->states.size() << "\n";
			}
	} //ok works we remove the state when we quit it cf. esq key

	//if no more states, end the application
	//BUT we still need to close the entire application when we remove the last state
	//Application end
	else
	{
		// std::cout << "Game::update() this->states.empty()=true" << "\n";
		// std::cout << "this->states.size = " << this->states.size() << "\n";
		// std::cout << "Game::update() this->endApplication()" << "\n";
		this->endApplication();
		this->window->close();
	}
	
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the game.
 * Clears the window.
 * If the states stack is not empty, it renders the top state.
 * If the states stack is empty, it ends the application.
 */
void Game::render()
{
	this->window->clear();

	//Render items
	if (!this->states.empty()) 
		this->states.top()->render(this->window); //render the top state = the current state

	this->window->display();
}

/**
 * @brief Runs the game.
 * Big loop that runs the game.
 * Updates the time delta.
 * Updates the game.
 * Renders the game.
 */
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}