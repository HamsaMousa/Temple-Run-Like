//very small class to hold the config for the game state
#ifndef GAMESTATECONFIG_HPP
#define GAMESTATECONFIG_HPP


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


class GameStateConfig {
public:
    int numberlives = 5; //by default
    float difficulty = 1.5; //by default

    GameStateConfig()
    {
        std::cout << "GameStateConfig constructor called" << std::endl;
    }
    //by default music is on
};

#endif //GAMESTATECONFIG_HPP