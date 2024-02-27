#include "HitboxCompo.hpp"

// ----------------------------------------------------------
// Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructor for HitboxCompo. Initializes the hitbox for the sprite.
 * 
 * Just created the hitbox according to the parameters.
 * Every entity will have a hitbox.
 *
 * @param sprite Reference to sprite to which this hitbox is tied.
 * @param offset_x Offset in x-direction of the hitbox relative to sprite's position.
 * @param offset_y Offset in y-direction of the hitbox relative to sprite's position.
 * @param width Width of the hitbox.
 * @param height Height of the hitbox.
 * @param shapeType The shape type of the hitbox, either a rectangle or a circle.
 */
//NEW WITH DIFFERENTS TYPES OF HITBOX
HitboxCompo::HitboxCompo(sf::Sprite& sprite, 
    float offset_x, float offset_y, 
    float width, float height,
    HitboxShape shapeType)
    :sprite(sprite), offsetX(offset_x), offsetY(offset_y), shapeType(shapeType)
{
    if (shapeType == HitboxShape::Rectangle) {
        this->rectangleHitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
        this->rectangleHitbox.setSize(sf::Vector2f(width, height));
        this->rectangleHitbox.setFillColor(sf::Color::Transparent);
        this->rectangleHitbox.setOutlineThickness(1.f);
        this->rectangleHitbox.setOutlineColor(sf::Color::Green);
    }
    else if(shapeType == HitboxShape::Circle){
        this->circleHitbox.setScale(1,1.4);
        this->circleHitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
        this->circleHitbox.setRadius(width / 2); // Assuming width = height = diameter of circle.
        this->circleHitbox.setFillColor(sf::Color::Transparent);
        this->circleHitbox.setOutlineThickness(1.f);
        this->circleHitbox.setOutlineColor(sf::Color::Green);
    }
}

/**
 * @brief Destructor for HitboxCompo.
 * Nothing to do here.
 */
HitboxCompo::~HitboxCompo()
{

}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Sets the scale for the hitbox.
 * Allow to ajust the hitbox the most accurately possible based on the sprite/texure.
 *
 * @param x Scale in x-direction.
 * @param y Scale in y-direction.
 */
void HitboxCompo::setScale(float x, float y)
{
    if(this->shapeType == HitboxShape::Rectangle)
        this->rectangleHitbox.setScale(x,y);
    else
        this->circleHitbox.setScale(x,y);
}

/**
 * @brief Get the position of the hitbox.
 * Will serve to update collision between entities.
 *
 * @return Returns the position of the hitbox as a 2D vector.
 */
const sf::Vector2f& HitboxCompo::getPosition() const
{
    if(this->shapeType == HitboxShape::Rectangle)
        return this->rectangleHitbox.getPosition();
    else
        return this->circleHitbox.getPosition();
}


/**
 * @brief Get the global bounds of the hitbox.
 * 
 * Used to check if two hitboxes are colliding.
 *
 * @return Returns a FloatRect object which contains the global bounds of the hitbox.
 */
const sf::FloatRect HitboxCompo::getGlobalBounds() const
{
    if(this->shapeType == HitboxShape::Rectangle)
        return this->rectangleHitbox.getGlobalBounds();
    else
        return this->circleHitbox.getGlobalBounds();
}

/**
 * @brief Check if the hitbox intersects with a given FloatRect object.
 *
 * Method called in the gamestate to check if two hitboxes are colliding.
 * 
 * @param frect The FloatRect object to check intersection with.
 * @return Returns true if the hitbox intersects with frect, false otherwise.
 */
bool HitboxCompo::checkintersects(const sf::FloatRect& frect)
{

    if(this->shapeType == HitboxShape::Rectangle)
        return this->rectangleHitbox.getGlobalBounds().intersects(frect);
    else
        return this->circleHitbox.getGlobalBounds().intersects(frect);
}

// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Update the position of the hitbox based on its linked sprite.
 *
 * This method is called in the game loop.
 */
void HitboxCompo::update()
{

    if(this->shapeType == HitboxShape::Rectangle)
        this->rectangleHitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
    else
        this->circleHitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}


// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the hitbox on the target RenderTarget.
 * Mostly used for debugging purposes.
 *
 * @param target The RenderTarget to draw the hitbox on.
 */
void HitboxCompo::render(sf::RenderTarget& target)
{
    //target.draw(this->hitbox);
    //NEW MOI
    if(this->shapeType == HitboxShape::Rectangle)
        target.draw(this->rectangleHitbox);
    else
        target.draw(this->circleHitbox);
}
