#include "Button.hpp"


// ----------------------------------------------------------
// Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new Button object.
 *
 * @param x The x-coordinate of the button's position.
 * @param y The y-coordinate of the button's position.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param font The font of the button's text.
 * @param text The text displayed on the button.
 * @param character_size The size of the characters in the button's text.
 * @param text_idle_color The color of the text when the button is idle.
 * @param text_hover_color The color of the text when the button is being hovered over.
 * @param text_active_color The color of the text when the button is being clicked.
 * @param idle_color The color of the button when idle.
 * @param hover_color The color of the button when being hovered over.
 * @param active_color The color of the button when being clicked.
 */
Button::Button(float x, float y, float width, float height,
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    this->buttonState = BTN_IDLE; 

    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->shape.setFillColor(idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);

    //SFML treats the top of the text as its origin, so we need to move it down by half of its height and width to center it
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );

    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f),
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)
    );


    // this->text.setPosition(
    //     this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
    //     this->shape.getPosition().y + (this->shape.getGlobalBounds().height/2.f) - this->text.getGlobalBounds().height/2.f
    // ); //to center the button on the screen 
    

    this->textIdleColor = text_idle_color; 
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
    
    
}

/**
 * @brief Destructor of the Button object.
 */
Button::~Button()
{

}


// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Checks if the button is being pressed.
 *
 * @return true if the button is being pressed, false otherwise.
 */
const bool Button::isPressed() const
{
    if(this->buttonState == BTN_ACTIVE)
    {
        return true;
    }
    return false;
}

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the state of the button based on the mouse's position.
 *
 * @param mousePos The current position of the mouse.
 */
void Button::update(const sf::Vector2f& mousePos) 
{
    //IDLE
    this->buttonState = BTN_IDLE; 

    //HOVER
    if(this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        //CLICK 
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		//this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		//this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		// this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default: /*For Debug if problem occurs*/
		this->shape.setFillColor(sf::Color::Red); 
		this->text.setFillColor(sf::Color::Blue);
		// this->shape.setOutlineColor(sf::Color::Green);
		break;
	}

}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the button on the given target.
 *
 * @param target The render target to draw the button on.
 */
void Button::render(sf::RenderTarget& target) 
{
    target.draw(this->shape);
    target.draw(this->text);
}