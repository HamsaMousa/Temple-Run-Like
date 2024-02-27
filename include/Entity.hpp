#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GeneInc.hpp"

#include "MovementCompo.hpp" 
#include "AnimationCompo.hpp" 
#include "HitboxCompo.hpp" 

class Entity 
{
private:
    void initVariables(); 

protected:

    //sf::Texture* texture;  //not even needed
    //sf::Sprite *sprite; 

    sf::Sprite sprite; //we force a sprite in a entity

    //now we have the class movementcompo
    MovementCompo* movementComponent; 
    AnimationCompo* animationComponent; 
    HitboxCompo* hitboxComponent; 

public:
    Entity();
    virtual ~Entity();

    void setTexture(sf::Texture& texture); 

    void createMovementComponent(const float maxVelocity,const float acceleration, const float deceleration); 
    void createAnimationComponent(sf::Texture& texture_sheet); 
    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, HitboxShape shapeType);

    virtual void setPosition(const float x, const float y); 
    virtual void movesmooth( const float& dt,const float dir_x, const float dir_y);
    virtual void movelane( const float& dt,const float dir_x, const float dir_y, const int idplayer);
    
    virtual void update(const float& dt); //not pure virtual to test 

    virtual void render(sf::RenderTarget& target);

    HitboxCompo* getHitboxComponent() const;

};

#endif // ENTITY_HPP