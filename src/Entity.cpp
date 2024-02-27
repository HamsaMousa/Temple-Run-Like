#include "Entity.hpp"

// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initializes the Entity's variables,
 * especially the pointers of the components to nullptr at the start to avoid errors
 */
void Entity::initVariables() 
{
    //this->texture = nullptr;  //we dont have a texture in entity now

    //now movementcompo class :
    this->movementComponent = nullptr; 
    this->animationComponent = nullptr; 
    this->hitboxComponent = nullptr; 
}

// ----------------------------------------------------------
// Constructors / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new Entity object.
 */
Entity::Entity()
{

    this->initVariables(); 

}

/**
 * @brief Destroys the Entity object.
 */
Entity::~Entity()
{
    delete this->movementComponent; 

    delete this->animationComponent; 

    delete this->hitboxComponent; 
}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Sets the texture of the entity.
 *
 * @param texture The texture to be set.
 */
void Entity::setTexture(sf::Texture& texture) 
{

    //this->sprite = new sf::Sprite(*this->texture); 
    this->sprite.setTexture(texture); 
}

/**
 * @brief Creates a new movement component for the entity.
 *
 * @param maxVelocity The maximum velocity of the entity.
 * @param acceleration The acceleration of the entity.
 * @param deceleration The deceleration of the entity.
 */
void Entity::createMovementComponent(const float maxVelocity,const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementCompo(this->sprite, maxVelocity,acceleration,deceleration ); 
}

/**
 * @brief Creates a new animation component for the entity.
 *
 * @param texture_sheet The texture sheet to be used for animations.
 */
void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	this->animationComponent = new AnimationCompo(this->sprite, texture_sheet);
}

/**
 * @brief Creates a new hitbox component for the entity.
 *
 * @param sprite The sprite for the hitbox.
 * @param offset_x The x-coordinate offset of the hitbox.
 * @param offset_y The y-coordinate offset of the hitbox.
 * @param width The width of the hitbox.
 * @param height The height of the hitbox.
 * @param shapeType The shape type of the hitbox.
 */
void Entity::createHitboxComponent(sf::Sprite& sprite, 
    float offset_x, float offset_y, 
    float width, float height, 
    HitboxShape shapeType)
{
    this->hitboxComponent = new HitboxCompo(sprite, offset_x, offset_y, width, height, shapeType);
}

/**
 * @brief Returns the entity's hitbox component.
 *
 * @return A pointer to the entity's hitbox component.
 */
HitboxCompo* Entity::getHitboxComponent() const {
    return this->hitboxComponent;
}

/**
 * @brief Sets the position of the entity.
 *
 * @param x The x-coordinate of the entity's position.
 * @param y The y-coordinate of the entity's position.
 */
void Entity::setPosition(const float x, const float y)
{
    // if(this->sprite)
    // {
    //     this->sprite->setPosition(x, y);
    // }

    //now we forced a sprite in a entity so no check needed
    this->sprite.setPosition(x, y);
}

/**
 * @brief Moves the entity smoothly (for up and down movement)
 *
 * @param dt The time delta since the last frame.
 * @param dir_x The x direction to move in.
 * @param dir_y The y direction to move in.
 */
void Entity::movesmooth(const float& dt,const float dir_x, const float dir_y)
{
    if(this->movementComponent)
    {
        this->movementComponent->movesmoothplayer(dt,dir_x, dir_y);  //sets velocity
    }
}

/**
 * @brief Moves the entity betwenn the lanes (for left and right movement)
 * It depends on the id of the player to know which lane to move to.
 * Each player has 3 lanes.
 *
 * @param dt The time delta since the last frame.
 * @param dir_x The x direction to move in.
 * @param dir_y The y direction to move in.
 * @param idplayer The ID of the player.
 */
void Entity::movelane(const float& dt,const float dir_x, const float dir_y,const int idplayer)
{
    //std::cout << "Entity::move with idplayer MOI" << idplayer << std::endl;
    if(this->movementComponent)
    {
        this->movementComponent->movelaneplayer(dt,dir_x, dir_y,idplayer);  //sets position
    }
}


// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Updates the entity.
 * Here especially the update will be done in the child class.
 *
 * @param dt The time delta since the last frame.
 */
void Entity::update(const float& dt) 
{    
    // if(this->movementComponent)
    //     this->movementComponent->update(dt);
    //NOW DONE IN childs
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders the entity on the given target.
 *
 * @param target The render target to draw the entity on.
 */
void Entity::render(sf::RenderTarget& target) 
{
    //if(target)   
        target.draw(this->sprite);
    
    //IF WE WANT TO SHOW THE HITBOXES
    // if(this->hitboxComponent)
    // {
    //     this->hitboxComponent->render(target);
    // }
    
}