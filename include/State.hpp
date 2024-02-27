#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include "Player.hpp" 
#include "Obstacle.hpp" //MOI OBSTACLES 28.05.2023
#include "Coin.hpp" 

#include <stack> 
#include <map> 

class State
{
private:
    /* data */

protected: 
    std::stack<State*>* states;
    //points to the original stack of states in the game class !!

    sf::RenderWindow *window;
    std::map<std::string, int>* supportedKeys; 
    std::map<std::string, int> keybinds; //each state will have its own keybinds
    
    bool quit;  
    bool paused;  

    //for not spamming a key
	float keytime;
	float keytimeMax;
    
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Ressources
    // changed to map:
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds() = 0; //

public:
    State(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states); 

    virtual ~State(); //Virtual destructor because we will inherit from this class and we want to avoid memory leaks
    
    //accessors
    const bool& getQuit() const; 
    const bool getKeytime(); // IMPORTANT
    
    virtual void endState(); 

    void pauseState(); 
    void unpauseState(); 
   
    virtual void updateInput(const float& dt) =0; 
    virtual void updateMousePositions(/*sf::View* view = nullptr*/);

    virtual void updateKeytime(const float& dt); // IMPORTANT 

    //Functions
    virtual void update(const float& dt) = 0; //Pure virtual function, we will not be able to create an object of this class
    virtual void render(sf::RenderTarget *target=nullptr) = 0;
};

#endif
