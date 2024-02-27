#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define LANE_WIDTH 136

#include "State.hpp" /*qui contient entity.h so ok*/
#include "PauseMenu.hpp"
#include "GameoverMenu.hpp" 
#include "Gui.hpp" 

#include "GameStateConfig.hpp"

class GameState : public State
{
    private:
        
        PauseMenu* pmenu;
        sf::Font font; 

        GameoverMenu* gameomenu;
        bool gameover;

        sf::RectangleShape background;
        sf::Texture backgroundTexture;

        sf::VertexArray divideLanes;
        float cooldownPlayer1;
        float cooldownPlayer2;
        float cooldownTime;

        Player* player; //pointer because dynamic allocation
        Player* player2; 

        sf::Text winnerText;

        //Systems
        unsigned points1;
        unsigned points2;

        //Obstacles
        //SpawnTimer is the time between each obstacle spawned
        float spawnTimer;
        float spawnTimerMax;
        std::vector<Obstacle*> obstaclesPlayer1;
        std::vector<Obstacle*> obstaclesPlayer2;

        //for the speed of the obstacles
        sf::Clock gameClock;

        bool laneOccupied[3] = {false, false, false}; // Flag to indicate if a lane is occupied

        //Coins
        float spawnTimerCoin;
        float spawnTimerCoinMax;
        std::vector<Coin*> coinsPlayer1;
        std::vector<Coin*> coinsPlayer2;

        float vitesseinstantT;

        Gui* gui2; 
        void initGui2();

        GameStateConfig * config;
        int maxlifeset;


        //Functions
        void initKeybinds(); 
        void initFonts(); 
        void initTextures(); 
        void initBackground(); 
        void initPauseMenu(); 
        void initGameoverMenu(); 
        void initPlayers();  //because Player is dynamic allocation
        void initLaneDividers(); 
        void initObstacles(); 
        void initCoins(); 
        void initScore(); 

        void centerText(sf::Text& text, int screenWidth);

    public:
        GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states,GameStateConfig* config); 

        virtual ~GameState();

        //Functions
        //void endState(); //enleve car dans state.cpp mtn

        virtual void updatePlayerInput(const float& dt); 

        void updateInput(const float& dt); //for pause menu
        void updateGameover(); 
        void updatePauseMenuButtons(); 
        void updateGameoverMenuButtons(); 

        void update(const float& dt);
        void render(sf::RenderTarget *target=nullptr);

        void updateObstacles(const float& dt);
        void updateCoins(const float& dt); 
        void updateEntitiesandCollision(const float& dt); 
        void updateEntitieandSpawn(const float& dt);
        void renderEntities(sf::RenderTarget *target=nullptr);
        float calculateEntitiesSpeed(); 
    
};

#endif //GAMESTATE_HPP
