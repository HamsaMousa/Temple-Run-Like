#ifndef HITBOXCOMPO_HPP
#define HITBOXCOMPO_HPP

#include "GeneInc.hpp"

enum class HitboxShape {
    Rectangle,
    Circle
};


class HitboxCompo
{
private:
    //hitbox itself not going to have a sprite
    //but we will have a reference to the sprite that we want to have a hitbox
    //sprite that belongs to the entity
    sf::Sprite& sprite;
    
    
    HitboxShape shapeType;
    sf::CircleShape circleHitbox;
    sf::RectangleShape rectangleHitbox; 
    //.. shape and not just shape because we might want to see the hitbox

    float offsetX;
    float offsetY;


public:
    HitboxCompo(sf::Sprite& sprite, float offset_x, float offset_y,float width, float height, HitboxShape shapeType);
    //offset_x and offset_y are the offset from the sprite position 

    virtual ~HitboxCompo();

    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

    //Setters
    //void setPosition(const sf::Vector2f& position);
    //void setPosition(const float x, const float y);
    //void setOffset(const float x, const float y);
    //void setOffset(const sf::Vector2f& offset);
    //void setNextPosition(const sf::Vector2f& velocity, const float& dt);
    void setScale(float x, float y);

    //Functions
    bool checkintersects(const sf::FloatRect& frect);
    void update();
    void render(sf::RenderTarget& target);

};



#endif // HITBOXCOMPO_HPP