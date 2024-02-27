#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
private:

    bool attacking;
    int lives = 5;  // Number of lives the player has //NEW

    //Functions
    void initVariables(int maxlifeset); 
    void initComponents();

public:
    //Player(float x, float y, sf::Texture* texture);
    Player(float x, float y, sf::Texture& texture_sheet, int maxlifeset); 
    
    virtual ~Player();

    void setScale(float x, float y);

    virtual void update(const float& dt); 
    virtual void updateAnimation(const float& dt);

    // A getter for the player's lives
    int getLives() const;
    // Method to decrease player's lives
    void loseLife();

    float getMovementSpeed() const;
    sf::FloatRect getGlobalBounds() const;

};
#endif // PLAYER_HPP