#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Entity.hpp"

class Obstacle : public Entity
{
protected:
    float speed;
    float speedScalingFactor;
    int hp;
    int hpMax;
    int damage;
    int lane;

    //sf::Sprite spriteobs;
    //sf::Texture textureobs;

    void initVariables(float speed);

    //void initTexture();
    //void initSprite();

public:
    Obstacle(float pos_x, float pos_y, sf::Texture& texture_sheet, float speed);

    ~Obstacle();

    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const int& getDamage() const;
    const float& getSpeed() const;
    const int& getLane() const;

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    bool checkIntersects(const sf::FloatRect& frect);

    void setLane(const int lane);

    void update(const float & dt);
    void updateAnimation(const float & dt);

    //void render(sf::RenderTarget& target);
};

#endif
