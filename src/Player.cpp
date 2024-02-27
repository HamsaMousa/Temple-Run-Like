#include "Player.hpp"

// ----------------------------------------------------------
//Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes player variables.
 * @param maxlifeset The initial number of lives for the player.
 */
void Player::initVariables(int maxlifeset) 
{
    this->attacking = false; 
    this->lives = maxlifeset;
}

/**
 * @brief Initializes player components.
 * Moved to the constructor directly.
 */

void Player::initComponents()
{
    // this->createMovementComponent(300.f,15.f,5.f); 
    // this->createAnimationComponent(this->texture_sheet); 
    //TOUT MIS DANS LE CONSTRUCTEUR DIRECTEMENT 
}

// ----------------------------------------------------------
//Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Player constructor.
 * Sets player position, scales player sprite, creates hitbox component, movement component, and animation component.
 * Also add animations to the animation component based on the texture sheet and the direction.
 * 
 * @param x X-coordinate for the initial player position.
 * @param y Y-coordinate for the initial player position.
 * @param texture_sheet Texture sheet for the player.
 * @param maxlifeset The initial number of lives for the player.
 */
Player::Player(float x, float y, sf::Texture& texture_sheet, int maxlifeset)  
{

    this->initVariables(maxlifeset);    //std::cout << "Player::initVariables" << "\n";
    this->initComponents();             //std::cout << "Player::initComponents" << "\n";

    this->setPosition(x, y);

    this->setScale(2.f, 2.f); //TEST AJUSTEMENT

    //std::cout << "this->createHitboxComponent, in Player::Player(..)" << "\n";
    this->createHitboxComponent(this->sprite, 20.f, 10.f, 88.f,110.f, HitboxShape::Circle);

    //std::cout << "this->createMovementComponent // determine speed,acc,decc A MODIF SI BESOIN" << "\n";
    this->createMovementComponent(300.f,15.f,5.f); //speed,acc,decc

    //std::cout << "this->createAnimationComponent" << "\n";
    this->createAnimationComponent(texture_sheet); 

    //spped, xcolstart, ycolstart, xcolend, ycolend, width, height
    this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 8, 0, 64, 64);
    this->animationComponent->addAnimation("WALK_LEFT", 10.f, 4, 1, 7, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 8, 1, 11, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_UP", 10.f, 12, 1, 15, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 1, 3, 1, 64, 64);
}

/**
 * @brief Player destructor.
 * Nothing to do here.
 */
Player::~Player()
{

}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Sets the scale of the player sprite.
 * @param x X-scale factor.
 * @param y Y-scale factor.
 */
void Player::setScale(float x, float y)
{
    this->sprite.setScale(x, y); 
}

/**
 * @brief Retrieves the current number of lives for the player.
 * Used in the gamestate class to verify the game over condition.
 * 
 * @return Number of player lives.
 */
int Player::getLives() const 
{
    return this->lives;
}

/**
 * @brief Decreases the number of player lives by one, as long as the current number of lives is greater than zero.
 * Used in the gamestate class so the player loses a life when colliding with an obstacle.
 */

void Player::loseLife() 
{
    if (this->lives > 0)
        this->lives--;
}

/**
 * @brief Get the speed from the movement component object
 * 
 * @return The max velocity of the movement component 
 */
float Player::getMovementSpeed() const
{
    return this->movementComponent->getMaxVelocity();
}

/**
 * @brief Gets the bounds of the sprite
 * 
 * @return The floatrectangle of the bounds
 */
sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}



// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the player's animation based on the movement state.
 * Basicly here all possible animations are added to the animation component.
 * So depending on the movement wanted, the corresponding animation will be played.
 * @param dt Time interval to update the animation for.
 */
void Player::updateAnimation(const float & dt)
{
    
    if(this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(),false);
    }
    else if(this->movementComponent->getState(MOVING_LEFT))
	{
        this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(),false);
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(),false);
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(),false);
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(),false);
    }
    //ATTTENTION GROS CRASH si dans le play le nom ecris existe pas !! cf. constructeur de player
}

/**
 * @brief Updates the player's movement, animation, and hitbox component by calling the corresponding update functions.
 * @param dt Time interval to update the player for.
 */
void Player::update(const float & dt)
{
    //std::cout << "Player::update" << "\n";
	this->movementComponent->update(dt); /*std::cout << "this->movementComponent->update(dt);" << "\n";*/
    
    this->updateAnimation(dt);

    this->hitboxComponent->update();
}
