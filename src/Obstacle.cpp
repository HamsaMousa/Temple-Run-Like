#include "Obstacle.hpp"

// ----------------------------------------------------------
//Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the coin's variables.
 *
 * Espcially the speed of the obstacle.
 * Other variables are not used for now.
 * 
 * @param speed The initial speed of the coin.
 */
void Obstacle::initVariables(float speed) 
{
    //this->speedScalingFactor = 1.0f + (elapsedTime / 60.0f); // Adjust speed every minute
    //this->speed = speedScalingFactor;
    this->speed = speed;
    this->hpMax = 5;
    this->hp = this->hpMax;
    this->damage = 5;
}



// void Obstacle::initTexture() {
//     if (!this->textureobs.loadFromFile("assets/stone.png")) {
//         std::cout << "ERROR::OBSTACLE::INITTEXTURE::Could not load texture file." << std::endl;
//     }

//     //in the le gamestate  
// }

// void Obstacle::initSprite() {
//     this->sprite.setTexture(this->textureobs);

//     //in the gamestate 
// }

// ----------------------------------------------------------
//Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new Obstacle object.
 * This constructor initializes the Obstacle variables and sets its position.
 * It also creates a hitbox component for the Obstacle and an animation component.
 * But not a movement component because the Obstacle does not move from user input so no need
 * to surcharge the update function.
 * 
 * @param pos_x The x-coordinate of the obstacle's position.
 * @param pos_y The y-coordinate of the obstacle's position.
 * @param texture_sheet The texture sheet to be used for animations.
 * @param speed The initial speed of the obstacle.
 */
Obstacle::Obstacle(float pos_x, float pos_y, sf::Texture& texture_sheet, float speed) 
{
    this->initVariables(speed);

    //this->initTexture(); //no because texture already load in the gamestate to be used for all the obstacles
    //so less resources for the game
    this->setPosition(pos_x, pos_y);

    this->createHitboxComponent(this->sprite, 1.f, 10.f, 75.f,10.f, HitboxShape::Circle);
    this->hitboxComponent->setScale(1.0f, 0.8f);


    this->movementComponent=nullptr; //pas de mouvement comme pour un joueur pour les obstacles
    //direct dans la fonction update ou on move l'obstacle

    this->createAnimationComponent(texture_sheet);

    this->animationComponent->getSprite().setScale(0.5f, 0.5f); //NEW
    float offsetX = 15.0f;
    float offsetY = 15.0f;
    this->animationComponent->getSprite().move(offsetX, offsetY);

    this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 5, 0, 160, 160); //stonev3
    //this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 0, 0, 102, 96);

}

/**
 * @brief Destroys the Coin object.
 * Nothing to destroy here.
 */
Obstacle::~Obstacle() {}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Returns the Obstacle's position.
 *
 * @return The position of the Obstacle as a 2D vector.
 */
const sf::Vector2f& Obstacle::getPos() const 
{
    return this->sprite.getPosition();
}

/**
 * @brief Gets the global bounds of the Obstacle.
 * @return A floating point rectangle representing the global bounds of the Obstacle.
 */
const sf::FloatRect Obstacle::getBounds() const 
{
    return this->sprite.getGlobalBounds();
}

/**
 * @brief Gets the damage of the Obstacle.
 * @return The damage of the Obstacle.
 */
const int& Obstacle::getDamage() const 
{
    return this->damage;
}

/**
 * @brief Gets the speed of the Obstacle.
 * @return The speed of the Obstacle.
 */
const float& Obstacle::getSpeed() const 
{
    return this->speed;
}

/**
 * @brief Gets the lane of the Obstacle.
 * @return The lane of the Obstacle.
 */
const int& Obstacle::getLane() const
{
    return this->lane;
}

/**
 * @brief Sets the lane of the Obstacle.
 *
 * @param lane The lane to set.
 */
void Obstacle::setLane(const int lane)
{
    this->lane = lane;
}

/**
 * @brief Gets the bounds of the sprite
 * 
 * @return The floatrectangle of the bounds
 */
sf::FloatRect Obstacle::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

/**
 * @brief Gets the position of the Obstacle.
 *
 * @return The position of the Obstacle as a 2D vector.
 */
sf::Vector2f Obstacle::getPosition() const
{
    return this->sprite.getPosition();
}

/**
 * @brief checks if the obstacle intersects with the floatrect
 * 
 * @param frect The floatrect to check
 * @return true if the obstacle intersects with the floatrect
 * @return false if the obstacle does not intersect with the floatrect
 */
bool Obstacle::checkIntersects(const sf::FloatRect& frect) {
    return this->sprite.getGlobalBounds().intersects(frect);
}


// ----------------------------------------------------------
// Update 
// ----------------------------------------------------------
/**
 * @brief Updates the Obstacle's animation.
 * here only play the animation IDLE_FRONT
 * @param dt The time delta since the last frame.
 */
void Obstacle::updateAnimation(const float & dt)
{
    this->animationComponent->play("IDLE_FRONT", dt, 1.f, 300.f,false);

}

/**
 * @brief Updates the update.
 * Moves the coin down the screen.
 * Updates the hitbox.
 * Updates the animation.
 * @param dt The time delta since the last frame.
 */
void Obstacle::update(const float & dt) 
{
    this->sprite.move(0.f, this->speed);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}


// ----------------------------------------------------------
// Render 
// ----------------------------------------------------------

// le render is in entity.cpp 
// + NOW WE HAVE HITBOXCOMPONENT SO NO NEED HERE TO HANDLE HITBOX

// void Obstacle::render(sf::RenderTarget& target) {
//     sf::RectangleShape hitbox(sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height));
//     hitbox.setPosition(this->sprite.getPosition());
//     hitbox.setFillColor(sf::Color::Transparent);
//     hitbox.setOutlineThickness(2.f);
//     hitbox.setOutlineColor(sf::Color::Red);
//     target.draw(hitbox);
// }
