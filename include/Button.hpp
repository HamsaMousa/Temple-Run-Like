#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GeneInc.hpp"

/**
 * @brief Represents a button to be able to click on menus for example
 */
class Button 
{
private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    enum button_states{
        BTN_IDLE = 0,
        BTN_HOVER,
        BTN_ACTIVE
    };
    short unsigned buttonState;

public:
    Button(float x, float y, float width, float height,
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
    virtual ~Button();

    //Accessors
    const bool isPressed() const; 
    

    //Functions
    void update(const sf::Vector2f& mousePos); //to be able to click button 
    
    void render(sf::RenderTarget& target); 

};

#endif // BUTTON_HPP