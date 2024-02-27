#include "MovementCompo.hpp"

// ----------------------------------------------------------
//Constructors / Destructors 
// ----------------------------------------------------------
/**
 * @brief Construct a new MovementCompo::MovementCompo object
 * For the players also set the current lane to 2 (middle lane)
 * 
 * @param sprite The sprite to move.
 * @param maxVelocity The maximum velocity for the sprite.
 * @param acceleration The acceleration for the sprite.
 * @param deceleration The deceleration for the sprite.
 */
MovementCompo::MovementCompo(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    currentlane_player1=2;
    currentlane_player2=2; //each player start in the middle of their side
    //std::cout << "Constructeur MovementCompo initcurrentlaneplayer" << std::endl;
}

/**
 * @brief Destructor of the MovementComponent object
 * Nothing to do here.
 * 
 */
MovementCompo::~MovementCompo()
{

}

// ----------------------------------------------------------
//Accessors 
// ----------------------------------------------------------
/**
 * @brief Get the Max Velocity object for the entity (esp the player for us)
 * 
 * @return const float& The maximum velocity.
 */
const float& MovementCompo::getMaxVelocity() const
{
    return this->maxVelocity;
}

/**
 * @brief Get the Velocity object
 * 
 * @return const sf::Vector2f& The velocity vector.
 */
const sf::Vector2f& MovementCompo::getVelocity() const
{
    return this->velocity;
}

/**
 * @brief Get the current movement state.
 * Uses the values of the velocity vector to determine the state.
 * The state of the movement component is used to determine the animation of the sprite.
 * 
 * @param state The state to check.
 * @return const bool True if the sprite is in the provided state.
 */
const bool MovementCompo::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;

	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true; //if go to left velocity.x nagative
		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;
		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true; //atention if up velocity.y is neg since 0,0 top left corner
		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

// ----------------------------------------------------------
//Functions 
// ----------------------------------------------------------
/**
 * @brief Change lane of the player sprite. It moves player's sprite in lanes. 3 lanes for each player.
 * Here the movement is not smooth, it is instant (setposition of the sprite).
 * 
 * Based on the id of the player, the function will move the sprite to the appropriate lane.
 * 
 * @param dt The delta time for smooth movement.
 * @param dir_x The direction to move in the x-axis.
 * @param dir_y The direction to move in the y-axis.
 * @param idplayer The id of the player to move.
 */
void MovementCompo::movelaneplayer(const float &dt,const float dir_x, const float dir_y,const int idplayer) //for lanes only //right left //setposition not smooth movement
{
    const float spriteSize = 64 * 2;

    // Define the positions of the columns for both players
    const float columnPositionsPlayerOne[4] = {
        1.5 * LANE_WIDTH - spriteSize / 2+ 20,  // Column 1
        2.5 * LANE_WIDTH - spriteSize / 2+ 20,  // Column 2
        3.5 * LANE_WIDTH - spriteSize / 2+ 20   // Column 3
    };

    const float columnPositionsPlayerTwo[4] = {
        5.5 * LANE_WIDTH - spriteSize / 2+ 40,  // Column 5
        6.5 * LANE_WIDTH - spriteSize / 2+ 40,  // Column 6
        7.5 * LANE_WIDTH - spriteSize / 2+ 40   // Column 7
    }; //+40 = facteur ajustement

    float new_x;
    if(idplayer==1)
    {
        // Increment or decrement currentColumn based on direction input
        if (dir_x < 0 && currentlane_player1 > 1) // Moving left
        {
            currentlane_player1--;
        }
        else if (dir_x > 0 && currentlane_player1 < 3) // Moving right
        {
            currentlane_player1++;
        }

        // Set the x position to the appropriate column based on player
        new_x = columnPositionsPlayerOne[currentlane_player1 - 1];
    }

    if(idplayer==2)
    {
        // Increment or decrement currentColumn based on direction input
        if (dir_x < 0 && currentlane_player2 > 1) // Moving left
        {
            currentlane_player2--;
        }
        else if (dir_x > 0 && currentlane_player2 < 3) // Moving right
        {
            currentlane_player2++;
        }

        // Set the x position to the appropriate column based on player
        new_x = columnPositionsPlayerTwo[currentlane_player2 - 1];
    }

    // Keep the current y position
    float new_y = this->sprite.getPosition().y;

    // Set the new position of the sprite
    this->sprite.setPosition(new_x, new_y);
}

/**
 * @brief Moves the player's sprite in a smooth way. Not a setposition but a move.
 * Allow to play an animation of the sprite when moving. 
 * For us it is used for up and down movement only since we have lanes. But it can be used for left and right movement too.
 * 
 * Do a fisrt check to see if the player will still be on the screen after the movement.
 * 
 * @param dt The delta time for smooth movement.
 * @param dir_x The direction to move in the x-axis.
 * @param dir_y The direction to move in the y-axis.
 */
void MovementCompo::movesmoothplayer(const float &dt,const float dir_x, const float dir_y) //move no lane //for up and down only //smooth movement
{

    this->velocity.x += this->acceleration * dir_x; //pour avoir un temps acceleration
    this->velocity.y += this->acceleration * dir_y; 
    
    //Limit velocity
    if(std::abs(this->velocity.x) > this->maxVelocity) 
    {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
    }
    if(std::abs(this->velocity.y) > this->maxVelocity)
    {
        this->velocity.y = this->maxVelocity * ((this->velocity.y < 0.f) ? -1.f : 1.f);
    }

    //AND CHECK FOR BOUND
    //Proposed position
    sf::Vector2f proposedPosition = this->sprite.getPosition() + this->velocity * dt;

    //Checking boundaries based on speed
    if (proposedPosition.x < 0) 
    {
        proposedPosition.x = 0;
        this->velocity.x = 0;
    } 
    else if (proposedPosition.x + this->sprite.getGlobalBounds().width > WINDOW_WIDTH)
    {
        proposedPosition.x = WINDOW_WIDTH - this->sprite.getGlobalBounds().width;
        this->velocity.x = 0;
    }
        
    if (proposedPosition.y < 0) 
    {
        proposedPosition.y = 0;
        this->velocity.y = 0;
    } 
    else if (proposedPosition.y + this->sprite.getGlobalBounds().height > WINDOW_HEIGHT)
    {
        proposedPosition.y = WINDOW_HEIGHT - this->sprite.getGlobalBounds().height;
        this->velocity.y = 0;
    }

    //then call the update function for decceleration and final move 

}

/**
 * @brief Update the deceleration of the sprite based on its current velocity.
 * 
 * Contrinues to move the sprite even if the player is not pressing the key to create a smooth movement.
 * 
 */
void MovementCompo::updatedeceleration()
{
    //deceleration x positive number
    if (this->velocity.x > 0.f)
    {
        //deceleration x positive number
        this->velocity.x -= deceleration;
        (this->velocity.x < 0.f) ? this->velocity.x = 0.f : 0.f;
    }
    else if(this->velocity.x < 0.f) //left
    {
        //deceleration x negative number
        if (this->velocity.x < 0.f)
        {
            this->velocity.x += deceleration;
            (this->velocity.x > 0.f) ? this->velocity.x = 0.f : 0.f;
        }
    }
    //same for y
    if (this->velocity.y > 0.f)
    {
        //deceleration y positive number
        this->velocity.y -= deceleration;
        (this->velocity.y < 0.f) ? this->velocity.y = 0.f : 0.f;
    }
    else if(this->velocity.y < 0.f) //left
    {
        //deceleration y negative number
        if (this->velocity.y < 0.f)
        {
            this->velocity.y += deceleration;
            (this->velocity.y > 0.f) ? this->velocity.y = 0.f : 0.f;
        }
    }

}

/**
 * @brief Update the sprite's boundaries to prevent it from moving off-screen.
 * 
 * For the .x coordinate no problem theoerically since we have lanes.
 * But for the .y coordinate we need to check the boundaries to prevent the player from moving off-screen.
 * 
 * Do a second check to see if the player will still be on the screen after the movement since sometimes the player can go off-screen 
 * even with the first check based on the velocity.
 * 
 */
void MovementCompo::updatebounds()
{
    //Checking boundaries again after movement 
    sf::Vector2f proposedPosition = this->sprite.getPosition();

    //Checking boundaries
    if (proposedPosition.x < 0) 
    {
        proposedPosition.x = 0;
        this->velocity.x = 0;
    } 
    else if (proposedPosition.x + this->sprite.getGlobalBounds().width > WINDOW_WIDTH)
    {
        proposedPosition.x = WINDOW_WIDTH - this->sprite.getGlobalBounds().width;
        this->velocity.x = 0;
    }
        
    if (proposedPosition.y < 0) 
    {
        proposedPosition.y = 0;
        this->velocity.y = 0;
    } 
    else if (proposedPosition.y + this->sprite.getGlobalBounds().height > WINDOW_HEIGHT)
    {
        proposedPosition.y = WINDOW_HEIGHT - this->sprite.getGlobalBounds().height;
        this->velocity.y = 0;
    }
    
    //set the new position of the sprite
    this->sprite.setPosition(proposedPosition);


}

/**
 * @brief Update the state of the sprite. It's the general update function that calls other update methods.
 * 
 * @param dt The delta time for smooth movement.
 */
void MovementCompo::update(const float& dt)
{
    //Deceleration
    this->updatedeceleration();

    //Final move
    this->sprite.move(this->velocity * dt);

    //Last check for bound
    this->updatebounds();
    
}
