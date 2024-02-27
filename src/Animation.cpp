#include "Animation.hpp"

// ----------------------------------------------------------
// Constructorrs / Destructors
// ----------------------------------------------------------
/**
 * @brief Constructs a new Animation object.
 *
 * @param sprite_ani Sprite to be animated.
 * @param texture_sheet Texture sheet to be used for animation.
 * @param animation_timer Time between animation frames.
 * @param start_frame_x Starting frame x-coordinate on the texture sheet.
 * @param start_frame_y Starting frame y-coordinate on the texture sheet.
 * @param frames_x Number of frames in the x-direction on the texture sheet.
 * @param frames_y Number of frames in the y-direction on the texture sheet.
 * @param width Width of a frame.
 * @param height Height of a frame.
 */
Animation::Animation(sf::Sprite& sprite_ani, sf::Texture& texture_sheet, 
        float animation_timer, 
        int start_frame_x, int start_frame_y, 
        int frames_x, int frames_y,
        int width, int height)
        : sprite(sprite_ani), textureSheet(texture_sheet), timer(0.f), done(false),animationTimer(animation_timer), width(width), height(height)
{
    this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
    this->currentRect = this->startRect;
    this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

    this->sprite.setTexture(this->textureSheet, true);
    this->sprite.setTextureRect(this->startRect);
}

/**
 * @brief Destructor of the Animation object.
 */
Animation::~Animation() {} //ATTENTION need the {} sinon pas de definition du destructeur

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------
/**
 * @brief Checks if the animation is done.
 *
 * @return true if the animation is done, false otherwise.
 */
const bool& Animation::isDone() const
{
    return this->done;
}


/**
 * @brief Plays the animation.
 *
 * @param dt Time since the last frame.
 * @return true if the animation is done, false otherwise.
 */
const bool& Animation::play (const float& dt)
{
    this->done = false; 

    if(this->timer < this->animationTimer)
        this->timer += 100.f * dt;
    else
    {
        this->timer = 0.f;

        if(this->currentRect != this->endRect)
        {
            this->currentRect.left += this->width;
        }
        else
        {
            this->currentRect.left = this->startRect.left;
            this->done = true; 
        }
        this->sprite.setTextureRect(this->currentRect);
    }

    return this->done; 
}

/**
 * @brief Plays the animation with a speed modifier.
 *
 * @param dt Time since the last frame.
 * @param modifier_pourcent Speed modifier for the animation. 
 * The actual animation speed is multiplied by this value.
 * @return true if the animation is done, false otherwise.
 */
const bool& Animation::play (const float& dt, float modifier_pourcent)
{
    this->done = false; 

    if(modifier_pourcent < 0.5f)//check pourcentage 
        modifier_pourcent = 0.5f;

    if(this->timer < this->animationTimer) //update timer
    {
        this->timer += (modifier_pourcent) * 100.f * dt;
        //avec le modifier on peut ralentir ou accelerer l'animation 
        //pourcentage de la vitesse de l'animation modifier/modifier_max cad modifier_pourcent directement
    }
    else
    {
        this->timer = 0.f;  //reset timer

        if(this->currentRect != this->endRect) //Animate
        {
            this->currentRect.left += this->width;
        }
        else  //Reset
        {
            this->currentRect.left = this->startRect.left;
            this->done = true;  //animationEnd = true;
        }
        this->sprite.setTextureRect(this->currentRect);
    }

    return this->done; //return animationEnd;
}

/**
 * @brief Resets the animation.
 */
void Animation::reset()
{
    //ATTENTION on reset le timer a animationTimer et non a 0.f comme ca dans le play
    //on doit pas attendre que le timer monte a animationTimer pour reset l'animation 
    //et les rectangles de l'animation en gros
    this->timer = this->animationTimer;
    this->currentRect = this->startRect;
}
