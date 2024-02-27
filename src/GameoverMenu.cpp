#include "GameoverMenu.hpp"

// ----------------------------------------------------------
// Constructor / Destructor
// ----------------------------------------------------------
/**
 * @brief Constructs a new GameoverMenu object.
 * Nothing too complicated here, just init the background, boxbg and text.
 * @param window The render window.
 * @param font The font to be used.
 */
GameoverMenu::GameoverMenu(sf::RenderWindow &window, sf::Font &font)
	: font(font)
{
	// Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Init boxbg
	this->boxbg.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 3.f,
			static_cast<float>(window.getSize().y) - 60.f));
	this->boxbg.setFillColor(sf::Color(20, 20, 20, 200));
	this->boxbg.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->boxbg.getSize().x / 2.f,
		30.f);

	// Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("Game Over");
	this->menuText.setPosition(
		this->boxbg.getPosition().x + this->boxbg.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->boxbg.getPosition().y + 40.f);
}


/**
 * @brief Destroys the GameoverMenu object.
 * Make sure to delete all the buttons if there are any.
 */
GameoverMenu::~GameoverMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Get the Buttons object.
 *
 * @return std::map<std::string, Button *> & The buttons.
 */
std::map<std::string, Button *> &GameoverMenu::getButtons()
{
	return this->buttons;
}

/**
 * @brief Determines whether the specified key button is pressed.
 *
 * @param key The button key.
 * @return const bool True if the specified key button is pressed, False otherwise.
 */
const bool GameoverMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

/**
 * @brief Adds a button to the game over menu.
 * Simple method to simplify the code to create buttons in this special menu.
 * @param key The key to identify the button.
 * @param y The y-coordinate of the button.
 * @param text The text displayed on the button.
 */
void GameoverMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->boxbg.getPosition().x + this->boxbg.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new Button(
		x, y, width, height,
		&this->font, text, 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the game over menu.
 * Here especially, we update the buttons.
 * @param mousePos The current position of the mouse.
 */
void GameoverMenu::update(const sf::Vector2f &mousePos)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the game over menu.
 *
 * @param target The render target.
 */
void GameoverMenu::render(sf::RenderTarget &target)
{
	target.draw(this->background);
	target.draw(this->boxbg);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}