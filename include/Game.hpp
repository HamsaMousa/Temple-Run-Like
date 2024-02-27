#ifndef GAME_HPP
#define GAME_HPP

#include "GeneInc.hpp"
#include "MainMenuState.hpp" 
#include "GameStateConfig.hpp"

#include <fstream>
#include <sstream> //to get data
#include <typeinfo> //for prints of de UpdateInput() et getquit() 


class Game
{
private:
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes; 
	bool fullscreen; 


	sf::Clock dtClock;
	float dt;

	std::stack<State*> states; //cf. polymorphism + use of pointers

	std::map<std::string, int> supportedKeys;

	GameStateConfig * config;

	//Initialization
	void initVariables(); 
	void initWindow();
	void initKeys(); 
	void initStates();
	
	
public:
	/**
     * Get application controller singleton instance
     */
    static Game& getInstance();
	
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions
	void endApplication(); 

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif