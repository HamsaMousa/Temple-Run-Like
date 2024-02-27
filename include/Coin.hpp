#ifndef COIN_HPP
#define COIN_HPP

#include "Entity.hpp"

class Coin : public Entity
{
protected:
    float speed; /**< The speed at which the coin moves. */
    float speedScalingFactor; /**< The factor by which speed scales over time. */
    int hp; /**< The health points of the coin. */
    int hpMax; /**< The maximum health points of the coin. */
    int damage; /**< The damage the coin can cause. */
    int lane; /**< The lane the coin is in. */

    //sf::Sprite spriteobs;
    //sf::Texture textureobs;

    void initVariables(float speed);

public:
    Coin(float pos_x, float pos_y, sf::Texture& texture_sheet, float speed);

    ~Coin();

    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const int& getDamage() const;
    const float& getSpeed() const;
    const int& getLane() const;
    void setLane(const int lane);

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;


    void update(const float & dt);
    void updateAnimation(const float & dt);

    //void render(sf::RenderTarget& target);
};

#endif // !COIN_HPP
