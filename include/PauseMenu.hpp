#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "GeneInc.hpp"
#include "Button.hpp"

class PauseMenu
{
private:
    sf::Font& font;
	sf::Text menuText;
	
    sf::RectangleShape background;
	sf::RectangleShape boxbg;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font); //we force window and font thanks to references
	virtual ~PauseMenu();

    //Accessors
    std::map<std::string, Button*>& getButtons();

	//Functions
	//void update();
	const bool isButtonPressed(const std::string key); 
	void addButton(const std::string key, float y, const std::string text); 
	void update(const sf::Vector2f& mousePos); 
    
    void render(sf::RenderTarget& target);
};

#endif //PAUSEMENU_HPP
