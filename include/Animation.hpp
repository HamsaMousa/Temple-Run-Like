#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>


/**
 * @brief Class that create an animation for an entity.
 * It will be used in the AnimationCompo class.
 */
class Animation
{
public:
    //Variables
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    float animationTimer;
    float timer;
    bool done; 
    int width;
    int height;
    sf::IntRect startRect;
    sf::IntRect currentRect;
    sf::IntRect endRect;

    Animation(sf::Sprite& sprite_ani, sf::Texture& texture_sheet, 
        float animation_timer, 
        int start_frame_x, int start_frame_y,
        /*int end_x, int end_y,*/ 
        /*Plutot que d'avoir le end si on fait frames_x * width a la fin on reobtiens bien end_x par exemple  */ 
        int frames_x, int frames_y,
        int width, int height);
  
    virtual ~Animation(); 

    const bool& isDone() const;

    const bool& play (const float& dt);
        
    const bool& play (const float& dt, float modifier_pourcent);

    void reset();
};


#endif // ANIMATION_HPP
