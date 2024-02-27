#ifndef MOVEMENTCOMPO_HPP
#define MOVEMENTCOMPO_HPP

#define LANE_WIDTH 136
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720



#include "GeneInc.hpp"


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementCompo
{
private:
    sf:: Sprite& sprite; 

    //Variables
    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    int currentlane_player1;
    int currentlane_player2;


public:
    MovementCompo(sf::Sprite& sprite,float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementCompo();

    //accessors
    const float& getMaxVelocity() const; 
    const sf::Vector2f& getVelocity() const; 
    
    const bool getState(const short unsigned state) const; //version finale 

    //Functions
    void movesmoothplayer(const float &dt,const float dir_x, const float dir_y);
    void movelaneplayer(const float &dt,const float dir_x, const float dir_y,const int idplayer);
    
    void updatebounds();
    void updatedeceleration();
    void update(const float& dt);

};
#endif