#ifndef ANIMATIONCOMPO_HPP
#define ANIMATIONCOMPO_HPP

#include "GeneInc.hpp"
#include "Animation.hpp"

/**
 * @brief Class that handle animations of the entity.
 * It contains a map of animations, and a reference to the sprite of the entity.
 */
class AnimationCompo
{
private:

    //Variables
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation *> animations; 
    Animation* lastAnimation; //pour permettre le reset !!
    
    
    Animation* priorityAnimation; 


public:
    AnimationCompo(sf::Sprite& sprite, sf::Texture& texture_sheet); //we have to force the user to pass a sprite and a texture sheet, cant be null
    virtual ~AnimationCompo();

    //Accessor
	const bool& isDone(const std::string key);

    //Functions
    void addAnimation(const std::string key, 
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    const bool& play(const std::string key,const float& dt, const bool priority); 
    const bool& play(const std::string key,const float& dt, const float& modifier, const float& modifier_max, const bool priority); 

    sf::Sprite& getSprite();

};

#endif // ANIMATIONCOMPO_HPP