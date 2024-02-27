#include "State.hpp"

// ----------------------------------------------------------
// Constructor / Destructor
// ----------------------------------------------------------
/**
 * @brief Construct a new State object
 * 
 * Parent of all the states in the game.
 * 
 * @param window The window for which this state belongs.
 * @param supportedKeys A map of the supported keys and their actions.
 * @param states A stack of the current states.
 */
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
    this->window = window;
    this->quit = false; //by default we don't want to end the state
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->paused = false; 

    this->keytime = 0.f; 
	this->keytimeMax = 20.f;
}

/**
 * @brief Destroy the State object
 * 
 * Nothing to do here.
 */

State::~State()
{

}


// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Ends the current state.
 * 
 * Sets the quit variable to true.
 * 
 */
void State::endState()
{
    //std::cout << "State::endState, this->quit = true now" << "\n";
    this->quit = true;
}

/**
 * @brief Pause the current state.
 * 
 * Sets the paused variable to true.
 */

void State::pauseState()
{
    this->paused = true;
}

/**
 * @brief Unpause the current state.
 * 
 * Sets the paused variable to false.
 */
void State::unpauseState()
{
    this->paused = false;
}

/**
 * @brief Get the Quit status of the current state.
 * 
 * @return const bool& True if the current state is marked for termination.
 */
const bool& State::getQuit() const
{
    return this->quit;
}

/**
 * @brief Check if the time for key press has passed.
 * 
 * @return const bool True if the time for key press has passed.
 */
const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Update the current mouse positions.
 * 
 * Mostly used for clicking on buttons.
 */
void State::updateMousePositions(/*sf::View* view*/)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window); //because window is a pointer
    
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

/**
 * @brief Update the time since the last key press.
 * 
 * @param dt The delta time from the last frame.
 */
void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}