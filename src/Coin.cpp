#include "Coin.hpp"

// ----------------------------------------------------------
//Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the coin's variables.
 *
 * @param speed The initial speed of the coin.
 */
void Coin::initVariables(float speed) 
{
    this->speed = speed;
    this->hpMax = 5;
    this->hp = this->hpMax;
    this->damage = 5;
}


// ----------------------------------------------------------
//Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new Coin object.
 *
 * @param pos_x The x-coordinate of the coin's position.
 * @param pos_y The y-coordinate of the coin's position.
 * @param texture_sheet The texture sheet to be used for animations.
 * @param speed The initial speed of the coin.
 */
Coin::Coin(float pos_x, float pos_y, sf::Texture& texture_sheet, float speed) 
{
    this->initVariables(speed);

    //this->initTexture(); //ducoup non la texture est deja load dans le gamestate pour tout les obstacles
    //= moins de ressources pour le jeu
    //this->initSprite();
    this->setPosition(pos_x, pos_y);

    //this->createHitboxComponent(this->sprite, 10.f, 10.f, 64.f,64.f, HitboxShape::Circle);
    this->createHitboxComponent(this->sprite, 8.f, 8.f, 50.f, 50.f, HitboxShape::Circle);
    this->hitboxComponent->setScale(1.0f, 1.0f);


    this->movementComponent=nullptr; //pas de mouvement comme pour un joueur pour les coins
    //direct dans la fonction update ou on move l'obstacle

    this->createAnimationComponent(texture_sheet);
    this->animationComponent->getSprite().setScale(4.0f, 4.0f); //NEW

    float offsetX = 20.0f;
    float offsetY = 20.0f;
    this->animationComponent->getSprite().move(offsetX, offsetY);

    this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 5, 0, 16, 16); 
    
}

/**
 * @brief Destroys the Coin object.
 * Nothing to destroy here.
 */
Coin::~Coin() {}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Returns the coin's position.
 *
 * @return The position of the coin as a 2D vector.
 */
const sf::Vector2f& Coin::getPos() const 
{
    return this->sprite.getPosition();
}

/**
 * @brief Returns the bounds of the coin's sprite.
 *
 * @return The global bounds of the coin's sprite as a FloatRect.
 */
const sf::FloatRect Coin::getBounds() const 
{
    return this->sprite.getGlobalBounds();
}

/**
 * @brief Returns the damage of the coin.
 *
 * @return The damage of the coin.
 */
const int& Coin::getDamage() const 
{
    return this->damage;
}

/**
 * @brief Returns the speed of the coin.
 *
 * @return The speed of the coin.
 */
const float& Coin::getSpeed() const 
{
    return this->speed;
}

/**
 * @brief Returns the lane of the coin.
 *
 * @return The lane of the coin.
 */
const int& Coin::getLane() const
{
    return this->lane;
}

/**
 * @brief Sets the lane of the coin.
 *
 * @param lane The lane to set.
 */
void Coin::setLane(const int lane)
{
    this->lane = lane;
}

/**
 * @brief Gets the bounds of the sprite
 * 
 * @return The floatrectangle of the bounds
 */
sf::FloatRect Coin::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

/**
 * @brief Gets the position of the Obstacle.
 *
 * @return The position of the Obstacle as a 2D vector.
 */
sf::Vector2f Coin::getPosition() const{
    return this->sprite.getPosition();
}



// ----------------------------------------------------------
// Update 
// ----------------------------------------------------------
/**
 * @brief Updates the coin's animation.
 * here only play the animation IDLE_FRONT
 * @param dt The time delta since the last frame.
 */
void Coin::updateAnimation(const float & dt)
{
    this->animationComponent->play("IDLE_FRONT", dt, 1.f, 300.f,false);

}

/**
 * @brief Updates the coin.
 * Moves the coin down the screen.
 * Updates the hitbox.
 * Updates the animation.
 * @param dt The time delta since the last frame.
 */
void Coin::update(const float & dt) 
{
    this->sprite.move(0.f, this->speed);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

// ----------------------------------------------------------
// Render 
// ----------------------------------------------------------
// le render is in entity.cpp