#ifndef HELPSTATE_H
#define HELPSTATE_H

#include "State.hpp"
#include "Button.hpp"

class HelpState :
	public State
{
private:
	//Variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
	sf::Texture player1KeysTexture;
	sf::Texture player2KeysTexture;
	sf::Texture playersTexture;
	sf::Texture obstaclesTexture;
	sf::Texture coinsTexture;
	sf::Texture lifeTexture;

	sf::Font font;

	sf::Sprite player1Keys;
	sf::Sprite player2Keys;
	sf::Sprite players;
	sf::Sprite obstacles;
	sf::Sprite coins;
	sf::Sprite life;

	sf::Text player1KeysText;
    sf::Text player2KeysText;

	sf::Text gameElementsText;
	sf::Text playersText;
    sf::Text obstaclesText;
	sf::Text coinsText;
	sf::Text lifeText;

    sf::Text gameInstructionstitleText;
	sf::Text gameInstructionsText;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	HelpState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~HelpState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void updateText();
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);
};

#endif //HELPSTATE_H