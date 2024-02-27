#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP


#include "GameState.hpp" //already include state.hpp
#include "Button.hpp" 
#include "HelpState.hpp" 
#include "SettingState.hpp"
#include "GameStateConfig.hpp"

#include <fstream>
#include <sstream>

class MainMenuState : public State
{
    private:
        //variables 
        sf::RectangleShape background;
        sf::Texture backgroundTexture; 
        sf::RectangleShape overlay; 

        sf::Font font; 
        sf::Font font2; //for mouse pos debug

        std::map<std::string, Button*> buttons; 

        GameStateConfig * config;

        //Functions
        void initVariables(); 
        void initBackground(); 
        void initFonts(); 
        void initKeybinds(); 
        void initButtons(); 

        sf::Text retmousepos(); 
        std::vector<sf::Vector2f> calculateButtonPositions(int screenWidth, int screenHeight, int buttonWidth, int buttonHeight, int buttonCount, int spacing); 

    public:
        MainMenuState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,GameStateConfig* config); 
        virtual ~MainMenuState();

        //void endState(); //removed, in state.cpp now

        virtual void updateInput(const float& dt); 
        
        void update(const float& dt);
        void updateButtons(); 

        void render(sf::RenderTarget *target=nullptr);
        void renderButtons(sf::RenderTarget& target);
};

#endif //MAINMENUSTATE_HPP