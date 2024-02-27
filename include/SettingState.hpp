#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.hpp"
#include "Button.hpp"

#include "GameStateConfig.hpp"

#include <sstream>
#include <iomanip> //for std::setprecision

class SettingState :
	public State
{
private:
	//Variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
	sf::Font font;
	sf::Font fonttext;

	std::map<std::string, Button*> buttons;
	std::vector<sf::Vector2f> buttonPositions;

	//--------------------------------
	GameStateConfig * config;	

	//Text to display game states config
	sf::Text livesText;
	sf::Text difficultyText;

	//Functions
	void initText();
	void centerText(sf::Text& text, int screenWidth);
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	std::vector<sf::Vector2f> calculateButtonPositions(int screenWidth, int screenHeight, int buttonWidth, int buttonHeight, int buttonCount, int spacing); 

public:
	SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameStateConfig* config);
	virtual ~SettingState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif //SETTINGSTATE_H