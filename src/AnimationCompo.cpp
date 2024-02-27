#include "AnimationCompo.hpp"

// ----------------------------------------------------------
// Constructorrs / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new AnimationCompo object.
 *
 * @param sprite Sprite to be animated.
 * @param texture_sheet Texture sheet to be used for animation.
 */
AnimationCompo::AnimationCompo(sf::Sprite& sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr) 
{
	//std::cout << "AnimationCompo::AnimationCompo()" << std::endl;
	
}

/**
 * @brief Destructor of the AnimationCompo object.
 * Cleans up all animations stored.
 */
AnimationCompo::~AnimationCompo()
{
    for (auto &i : this->animations)
	{
		delete i.second; //second because we want to delete the animation and not the key
	}
}

// ----------------------------------------------------------
// Accessors
// ----------------------------------------------------------
/**
 * @brief Checks if a given animation is done.
 *
 * @param key Key to the animation to check.
 * @return true if the animation is done, false otherwise.
 */
const bool & AnimationCompo::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}



// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Adds an animation to the component.
 *
 * @param key Key to store the animation under.
 * @param animation_timer Time between animation frames.
 * @param start_frame_x Starting frame x-coordinate on the texture sheet.
 * @param start_frame_y Starting frame y-coordinate on the texture sheet.
 * @param frames_x Number of frames in the x-direction on the texture sheet.
 * @param frames_y Number of frames in the y-direction on the texture sheet.
 * @param width Width of a frame.
 * @param height Height of a frame.
 */
void AnimationCompo::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height
	);
}

/**
 * @brief Plays a given animation.
 *
 * @param key Key to the animation to play.
 * @param dt Time since the last frame.
 * @param priority Whether the animation has priority.
 * @return true if the animation is done, false otherwise.
 */
const bool& AnimationCompo::play(const std::string key, const float& dt, const bool priority)
{
	//if priority is true, we play the animation that is called priorityAnimation
	if (this->priorityAnimation)
	{
		if(this->priorityAnimation == this->animations[key])
		{
			//reset the last animation if it is different from the current one
			if (this->lastAnimation != this->animations[key])
			{
				if(this->lastAnimation == NULL)
				{
					//first time we play an animation
					this->lastAnimation = this->animations[key];
				}
				else
				{
					//if not null, reset the last animation
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}	
			}
			//avec le if mtn car play renvie un bool mtn
			if(this->animations[key]->play(dt))
			{
				//if the animation is finished, we reset the priority animation
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //if no priority set
	{
		if(priority)
		{
			this->priorityAnimation=this->animations[key]; 
		}
		//reset the last animation if it is different from the current one
		if (this->lastAnimation != this->animations[key])
		{
			if(this->lastAnimation == NULL)
			{
				//first time we play an animation
				this->lastAnimation = this->animations[key];
			}
			else
			{
				//if not null, reset the last animation
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}	
		}
		//cf. avant change pas
		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

//surcharge of fonction play to take a modifier of the speed
/**
 * @brief Plays a given animation with a speed modifier.
 *
 * @param key Key to the animation to play.
 * @param dt Time since the last frame.
 * @param modifier Speed modifier for the animation. The actual animation speed is multiplied by this value.
 * @param modifier_max Maximum possible value of the modifier.
 * @param priority Whether the animation has priority.
 * @return true if the animation is done, false otherwise.
 */
const bool& AnimationCompo::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) 
	{
		if(this->priorityAnimation == this->animations[key])
		{
			//reset the last animation if it is different from the current one
			if (this->lastAnimation != this->animations[key])
			{
				if(this->lastAnimation == NULL)
				{
					//first time we play an animation
					this->lastAnimation = this->animations[key];
				}
				else
				{
					//if not null, reset the last animation
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}	
			}
			//avec le if mtn car play renvie un bool mtn
			if(this->animations[key]->play(dt, std::abs(modifier / modifier_max)))
			{
				//if the animation is finished, we reset the priority animation
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		if(priority) //if no priority set
		{
			this->priorityAnimation=this->animations[key]; 
		}
		//reset the last animation if it is different from the current one
		if (this->lastAnimation != this->animations[key])
		{
			if(this->lastAnimation == NULL)
			{
				//first time we play an animation
				this->lastAnimation = this->animations[key];
			}
			else
			{
				//if not null, reset the last animation
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}	
		}
		//in the play of the animation, we pass % of speed of animation directly
		//+ avec des absolute values to not have any possible errors 
		this->animations[key]->play(dt, std::abs(modifier / modifier_max)); 
	}

	return this->animations[key]->isDone();
}

/**
 * @brief Gets the sprite of this AnimationCompo.
 * 
 * @return Reference to the sprite of this AnimationCompo.
 */
sf::Sprite& AnimationCompo::getSprite() {
    return this->sprite;
}
