#include "GameState.hpp"
#include <fstream>
#include <sstream> //to initkeybind from steam

#include <math.h> 

// ----------------------------------------------------------
// Initializer functions
// ----------------------------------------------------------
/**
 * @brief Initialize key bindings from a configuration file.
 * Opens the file gamestate_initkeybinds.ini and fills the map keybinds.
 */
void GameState::initKeybinds()
{

    //std::cout << "GameState::initKeybinds()"<< "\n";
    std::string ipath = "resources/gamestate_initkeybinds.ini";
    std::ifstream ifs(ipath);
    // VOIR LE CMAKE QUI COPIE RESOURCES DANS LE BUILD ET LA OK

    if (ifs.is_open())
    {
        std::cout << "Opened " + ipath + " file." << std::endl;
        std::string ikeybind = "";
        std::string ikey = "";
        while (ifs >> ikeybind >> ikey)
        {
            this->keybinds[ikeybind] = this->supportedKeys->at(ikey);
            // Le game charge toutes les supportedKeys dans un map depuis game_initkeys.ini
            // ensuite dans GameState on definit les keybind propres au State
            // en utilisant les supportedKeys deja chargees
            // et on y associe un nom "MOVE_LEFT" a la valeur de la key "Q" chargee depuis game_initkeys.ini
        }
    }
    else
    {
        std::cerr << "Cannot open" + ipath + " file." << std::endl;
    }
    ifs.close();
}

/**
 * @brief Load and set up the background texture.
 */
void GameState::initBackground()
{
    //std::cout << "GameState::initBackground() MOI"<< "\n";

    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)));

    // std::string ipath="assets/templebackground.jpg";
    std::string ipath = "assets/gamestatebackground.png";
    // error gestion
    if (!this->backgroundTexture.loadFromFile(ipath))
    {
        std::cout << "ERROR GameState::initBackground() COULD NOT LOAD BACKGROUND TEXTURE"
                << "\n";
    }

    this->background.setTexture(&this->backgroundTexture);
}

/**
 * @brief Load the font file.
 */
void GameState::initFonts()
{

    std::string ipath = "assets/28_Days_Later.ttf";
    //std::cout << "GameState::initFonts() " << "\n";

    if (!this->font.loadFromFile(ipath))
    {
        throw("ERROR GameState::initFonts() COULD NOT LOAD FONT");
    }
}

/**
 * @brief Load all textures for the game state.
 * So all the entities will not have to load their own textures.
 * It will be easier to manage the textures.
 */
void GameState::initTextures()
{
    // sf::Texture temp;
    // temp.loadFromFile("assets/Isaac.png");
    // this->textures["PLAYER_IDLE"] = temp; //MARCHE MAIS + RAPIDE DE FAIRE COMME CA:
    // if(!this->textures["PLAYER_IDLE"].loadFromFile("assets/Isaac.png"))
    //      throw "ERROR GameState::initTextures() COULD NOT LOAD PLAYER IDLE TEXTURE";

    //std::cout << "LoadFromFile PLAYER_SHEET"<< "\n";
    if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/PLAYER_SHEET2.png"))
    {
        throw "ERROR GameState::initTextures() COULD NOT LOAD PLAYER IDLE TEXTURE";
    }

    //std::cout << "LoadFromFile OBSTACLE_SHEET"<< "\n";
    if(!this->textures["OBSTACLE_SHEET"].loadFromFile("assets/projetastev3.png"))
    {
        throw "ERROR GameState::initTextures() COULD NOT LOAD OBSTACLE SHEET TEXTURE";
    }

    //std::cout << "LoadFromFile COIN_SHEET"<< "\n";
    if (!this->textures["COIN_SHEET"].loadFromFile("assets/coin.png"))
    {
        throw "ERROR GameState::initTextures() COULD NOT LOAD COIN_SHEET TEXTURE";
    }
}

/**
 * @brief Initialize the pause menu
 */
void GameState::initPauseMenu()
{
    //std::cout << "GameState::initPauseMenu()"<< "\n";
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 500.f, "Quit");
}

/**
 * @brief Initialize the game over menu.
 */
void GameState::initGameoverMenu()
{
    //std::cout << "GameState::initGameoverMenu()"<< "\n";
    this->gameomenu = new GameoverMenu(*this->window, this->font);
    
    this->gameover = false;

    this->gameomenu->addButton("QUIT", 500.f, "Quit");
}

/**
 * @brief Initialize the lane dividers.
 * Mostly a debug feature to see the lanes on the screen and verify the player's position.
 */
void GameState::initLaneDividers()
{
    divideLanes = sf::VertexArray(sf::Lines, 16);

    // set vertex positions with empty space added to x-coordinate
    divideLanes[0] = sf::Vertex({LANE_WIDTH + 24, 0}, sf::Color(255, 0, 0));
    divideLanes[1] = sf::Vertex({LANE_WIDTH + 18, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[2] = sf::Vertex({2 * LANE_WIDTH + 22, 0}, sf::Color(255, 0, 0));
    divideLanes[3] = sf::Vertex({2 * LANE_WIDTH + 20, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[4] = sf::Vertex({3 * LANE_WIDTH + 22, 0}, sf::Color(255, 0, 0));
    divideLanes[5] = sf::Vertex({3 * LANE_WIDTH + 18, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[6] = sf::Vertex({4 * LANE_WIDTH + 20, 0}, sf::Color(255, 0, 0));
    divideLanes[7] = sf::Vertex({4 * LANE_WIDTH + 18, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[8] = sf::Vertex({5 * LANE_WIDTH + 46, 0}, sf::Color(255, 0, 0));
    divideLanes[9] = sf::Vertex({5 * LANE_WIDTH + 40, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[10] = sf::Vertex({6 * LANE_WIDTH + 44, 0}, sf::Color(255, 0, 0));
    divideLanes[11] = sf::Vertex({6 * LANE_WIDTH + 40, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[12] = sf::Vertex({7 * LANE_WIDTH + 44, 0}, sf::Color(255, 0, 0));
    divideLanes[13] = sf::Vertex({7 * LANE_WIDTH + 40, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
    divideLanes[14] = sf::Vertex({8 * LANE_WIDTH + 40, 0}, sf::Color(255, 0, 0));
    divideLanes[15] = sf::Vertex({8 * LANE_WIDTH + 40, WINDOW_HEIGHT}, sf::Color(255, 0, 0));
}

/**
 * @brief Initialize the players.
 * Assign them to their initial lanes.
 * Create the player objects thanks to the textures loaded in the GameState.
 * Gives them a max life value based on the GameStateConfig object that can be updated thanks to the settings menu.
 */
void GameState::initPlayers()
{
    //std::cout << "GameState::initPlayers()"<< "\n";

    // Sprite size after scaling
    const float spriteSize = 64 * 2;

    // Assign players to their initial lanes
    // Adjust the lane positioning to be in the middle of the lane
    float player1Lane = (2.5 * LANE_WIDTH) - spriteSize / 2 + 20; // Between lanes 2 and 3
    float player2Lane = (6.5 * LANE_WIDTH) - spriteSize / 2 + 40; // Between lanes 6 and 7

    // Assign a default value for the y-position
    float defaultYPos = 500;

    this->player = new Player(player1Lane, defaultYPos, this->textures["PLAYER_SHEET"],maxlifeset);

    this->player2 = new Player(player2Lane, defaultYPos, this->textures["PLAYER_SHEET"],maxlifeset);

    // PERSO test OK
    // this->player->setScale(0.1f, 0.1f); // Set the scale of the player sprite
}

/**
 * @brief Initialize the Graphical User Interface (GUI) version 2.
 * This GUI is used to display the score and the lives of the players.
 * Lifes are displayed as hearts.
 * The score is displayed as a number.
 */
void GameState::initGui2() 
{
    this->gui2 = new Gui(this->font, maxlifeset);
}

/**
 * @brief Initialize the obstacles in the game.
 * Just define the spawn timer for the obstacles.
 */
void GameState::initObstacles()
{
    //std::cout << "GameState::initObstacles()" << "\n";

    this->spawnTimerMax = 50.f; 
    this->spawnTimer = this->spawnTimerMax;
}

/**
 * @brief Initialize the coins in the game.
 * Just define the spawn timer for the coins.
 */
void GameState::initCoins()
{
    //std::cout << "GameState::initCoins()"<< "\n";

    this->spawnTimerCoinMax = 50.f;
    this->spawnTimerCoin = this->spawnTimerMax;
}

/**
 * @brief Initialize the score of the players.
 * 0 points for each player at the beginning of the game.
 */
void GameState::initScore()
{
    //std::cout << "GameState::initScore()"<< "\n";

    this->points1 = 0;
    this->points2 = 0;
}


// ----------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------
/**
 * @brief Constructor of the GameState class.
 * Use the constructor of the State class to initialize the window, the supported keys and the states.
 * Get the GameStateConfig object to initialize the game state configuration needed for the 
 * game difficulty and the number of lives of the players.
 * call the different initialization methods and sets other attributes.
 * 
 * @param window Pointer to the RenderWindow object representing the window of the game.
 * @param supportedKeys Pointer to a map containing the supported keys.
 * @param states Pointer to a stack of State pointers representing the game's states.
 * @param config Pointer to the GameStateConfig object containing the game state configuration.
 */
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states,GameStateConfig* config)
    : State(window, supportedKeys, states), config(config) 
{
    // Seed the random number generator
    std::srand(std::time(NULL));

    
    if(this->config)
    {
        std::cout << "config difficulty : " << this->config->difficulty << "\n";
        std::cout << "config nb lifes : " << this->config->numberlives << "\n";
        maxlifeset = this->config->numberlives;
    }
    else
    {
        maxlifeset = 5;
    }


    this->initKeybinds();
    this->initFonts(); 
    this->initTextures();
    this->initBackground();
    this->initPauseMenu(); 
    this->initGameoverMenu();
    this->initPlayers(); //attention orders of init
    this->initGui2(); //v2 avec hearths
    this->initLaneDividers();     

    //define cooldown for movement and some other stuff
    cooldownPlayer1 = 0.0f;
    cooldownPlayer2 = 0.0f;
    cooldownTime = 0.2f;

    winnerText.setFont(font);  // Set the text's font
    winnerText.setCharacterSize(60);  // Set the text's size
    winnerText.setFillColor(sf::Color::Blue);  // Set the text's color
    winnerText.setPosition(this->window->getSize().x / 2.0f -100.0f, this->window->getSize().y / 2.0f);

    this->initObstacles();  // Initialize the obstacles
    this->initCoins();    // Initialize the coins 
    this->initScore();   // Initialize the score
}

/**
 * @brief Destructor of the GameState class.
 * Delete the player, the pause menu, the game over menu, the GUI, the obstacles and the coins.
 * Make sure to delete all the dynamically allocated memory.
 */
GameState::~GameState()
{
    delete this->player; //DON'T FORGET TO DELETE
    delete this->pmenu;  
    delete this->player2; 
    delete this->gameomenu; 

    // Delete obstacles 
    for (auto *i : this->obstaclesPlayer1)
    {
        delete i;
    }

    for (auto *i : this->obstaclesPlayer2)
    {
        delete i;
    }
    
    // Delete GUI object
    delete this->gui2;

    // Delete Coins
    for (auto *i : this->coinsPlayer1)
    {
        delete i;
    }
    for (auto *i : this->coinsPlayer2)
    {
        delete i;
    }

}

// ----------------------------------------------------------
// Functions
// ----------------------------------------------------------

/*
void GameState::endState()
{
    std::cout << "Ending GameState!" << "\n";
}
*/

/**
 * @brief Just a small utility function to center a text on the screen.
 */
void GameState::centerText(sf::Text& text, int screenWidth) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                textRect.top + textRect.height / 2.0f);
    float xPos = screenWidth / 2.0f;
    text.setPosition(xPos, text.getPosition().y);
}


// ----------------------------------------------------------
// Update
// ----------------------------------------------------------
/**
 * @brief Calculate the speed of the entities depending on the time elapsed since the beginning of the game.
 * The speed of the entities increases with time.
 * It used the GameStateConfig object to get the difficulty of the game aka the starting speed of the entities.
 */
float GameState::calculateEntitiesSpeed() {
    float elapsedTime = gameClock.getElapsedTime().asSeconds();

    float baseSpeed = 1.5f; 
    //speed depends on time and the starting difficulty
    if(this->config)
    {
        //std::cout << "ok config difficulty : " << this->config->difficulty << "\n";
        baseSpeed = this->config->difficulty;
    }

    float speed = baseSpeed + (elapsedTime / 60.0f); 

    if(speed > 4.5f) {
        speed = 4.5f;
    }
    return speed;
}

/**
 * @brief Update the coins
 * Certains chance to spawn a coin on the free lane available after spawning the obstacles
 * Push the coins in the vector of coins for each player
 * 
 * @param dt Time elapsed since the last update.
 */
void GameState::updateCoins(const float& dt)
{
    if(rand()%5 == 0) //20% chance spawning a coin
    {
        // Get the free lane
        int freeLane = -1; // Initialize to an invalid value
        for (int i = 0; i < 3; ++i) 
        {
            if (!this->laneOccupied[i]) 
            {
                freeLane = i;
                break; // We found a free lane, no need to keep checking
            }
        }

        if (freeLane == -1) 
        {
            // There are no free lanes, handle this situation accordingly
            std::cout << "PROBLEM There are no free lanes for the coin" << std::endl;
        } 
        else 
        {
            // Create new obstacles
            Coin *coin_p1 = nullptr;
            Coin *coin_p2 = nullptr;
            
            // Determine the spawn position based on the lane
            float spawnPos_p1 = 0.f;
            float spawnPos_p2 = 0.f;
            
            switch (freeLane) {
                case 0:
                    spawnPos_p1 = LANE_WIDTH + 35; //lane0_p1
                    spawnPos_p2 = this->window->getSize().x / 2 + LANE_WIDTH / 2 + 30; //lane0_p2
                    break;
                case 1:
                    spawnPos_p1 = 2 * LANE_WIDTH + 35; //lane1_p1
                    spawnPos_p2 = this->window->getSize().x / 2 + 2 * LANE_WIDTH - 40; //lane1_p2
                    break;
                case 2:
                    spawnPos_p1 = this->window->getSize().x / 2 - LANE_WIDTH - 60; //lane2_p1
                    spawnPos_p2 = this->window->getSize().x - (this->window->getSize().x / 2 - 3 * LANE_WIDTH + 40); //lane2_p2
                    break;
            }

            // Spawn the coins
            coin_p1 = new Coin(spawnPos_p1, -100.f, this->textures["COIN_SHEET"], this->vitesseinstantT);
            this->coinsPlayer1.push_back(coin_p1);

            coin_p2 = new Coin(spawnPos_p2, -100.f, this->textures["COIN_SHEET"], this->vitesseinstantT);
            this->coinsPlayer2.push_back(coin_p2);

            // std::cout << "Generated a coin in lane " << freeLane << std::endl;
            // get info about size of vecotr coinsplayer1 and 2
            // std::cout << "size of coinsPlayer1: " << coinsPlayer1.size() << std::endl;
            // std::cout << "size of coinsPlayer2: " << coinsPlayer2.size() << std::endl;

        }
    }
}


/**
 * @brief Update the obstacles
 * Randomly spawn obstacles on the 2/3 lanes available for each player
 * Both players have the same obstacles at the same time to keep the game fair
 * After spawning the obstacles, update the laneOccupied vector to know which lane is occupied
 * And push the obstacles in the vector of obstacles for each player
 * 
 * @param dt Time elapsed since the last update.
 */
void GameState::updateObstacles(const float& dt)
{
    //reset lane occupied
    for (int i = 0; i < 3; ++i) {
        this->laneOccupied[i] = false;
    }

    float lane0_p2 = this->window->getSize().x / 2 + LANE_WIDTH / 2 + 30;
    float lane1_p2 = this->window->getSize().x / 2 + 2 * LANE_WIDTH - 40;
    float lane2_p2 = this->window->getSize().x - (this->window->getSize().x / 2 - 3 * LANE_WIDTH + 40);

    float lane0_p1 = LANE_WIDTH + 35;
    float lane1_p1 = 2 * LANE_WIDTH + 35;
    float lane2_p1 = this->window->getSize().x / 2 - LANE_WIDTH - 60;


        //-100.f so that the obstacle will be spawned outside the window
        // Spawn obstacles on a random lane
        int obstacleLane = rand() % 3;

        // Create new obstacles
        Obstacle *obstacle1_p1 = nullptr;
        Obstacle *obstacle1_p2 = nullptr;

        Obstacle *obstacle2_p1 = nullptr;
        Obstacle *obstacle2_p2 = nullptr;

        // Create obstacles based on lane and texture
        if (obstacleLane == 0) // Left lane
        {
            obstacle1_p1 = new Obstacle(lane0_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
            obstacle1_p2 = new Obstacle(lane0_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);    
        }
        else if (obstacleLane == 1) // Middle lane
        {
            obstacle1_p1 = new Obstacle(lane1_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
            obstacle1_p2 = new Obstacle(lane1_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
        }
        else if (obstacleLane == 2) // Right lane
        {
            obstacle1_p1 = new Obstacle(lane2_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
            obstacle1_p2 = new Obstacle(lane2_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
        }

        if (obstacle1_p1 && obstacle1_p2)
        {
            // Set the initial lane
            obstacle1_p1->setLane(obstacleLane);
            obstacle1_p2->setLane(obstacleLane);

            // Determine if we need a second obstacle
            //bool secondObstacle = rand() % 2;
            //if (secondObstacle)
            //{
                // Determine the lane of the second obstacle, ensuring it's different from the first
                int secondObstacleLane = (obstacleLane + (rand() % 2 + 1)) % 3; // Will be either obstacleLane + 1 or obstacleLane + 2, then wrapped to be in [0, 2]

                // Change the lane of the second obstacle
                if (secondObstacleLane == 0) // Left lane
                {
                    obstacle2_p1 = new Obstacle(lane0_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                    obstacle2_p2 = new Obstacle(lane0_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                }
                else if (secondObstacleLane == 1) // Middle lane
                {
                    obstacle2_p1 = new Obstacle(lane1_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                    obstacle2_p2 = new Obstacle(lane1_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                }
                else if (secondObstacleLane == 2) // Right lane
                {
                    obstacle2_p1 = new Obstacle(lane2_p1, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                    obstacle2_p2 = new Obstacle(lane2_p2, -100.f, this->textures["OBSTACLE_SHEET"], this->vitesseinstantT);
                }

                if (obstacle2_p1 && obstacle2_p2)
                {
                    // Set the lane of the second obstacle
                    obstacle2_p1->setLane(secondObstacleLane);
                    obstacle2_p2->setLane(secondObstacleLane);

                    // Add the obstacles to the respective lists
                    this->obstaclesPlayer1.push_back(obstacle1_p1);
                    this->obstaclesPlayer1.push_back(obstacle2_p1);

                    this->obstaclesPlayer2.push_back(obstacle1_p2);
                    this->obstaclesPlayer2.push_back(obstacle2_p2);

                    //update line occupied
                    this->laneOccupied[obstacleLane] = true;
                    this->laneOccupied[secondObstacleLane] = true;

                }
            //}
        }

        

}

/**
 * @brief Updates game entities and manages their spawning.
 *
 * This function is responsible for updating the state of game entities, such as obstacles and coins, 
 * and handling their spawning based on certain conditions.
 * Updates the entities of the game and spawns new ones based on a spawn timer. 
 * The timer is incremented based on the game's clock and the entities' speed. 
 * If the spawn timer is greater than or equal to a set max timer, obstacles and coins are spawned, and the timer is reset.
 *
 * @param dt Time difference since the last frame.
 */
void GameState::updateEntitieandSpawn(const float & dt)
{

    float elapsedTime = gameClock.getElapsedTime().asSeconds();
    this->vitesseinstantT = calculateEntitiesSpeed();

    //this->spawnTimer += 0.1925; //seems good //higher = less time between obstacles //when speed = 1.0f obstacleSpeed
    //this->spawnTimer += 0.1925*2; //if 2.0f for obstacleSpeed
    float increasefact = 0.195*vitesseinstantT;
    this->spawnTimer += increasefact;

    /*
    //DEBUGGGGG
    system("clear"); //clear the terminal
    std::string info;
    info += "elapsedTime: " + std::to_string(elapsedTime) + "\n";
    info += "vitesseinstantT: " + std::to_string(this->vitesseinstantT) + "\n";
    info += "increasefact: " + std::to_string(increasefact) + "\n";
    info += "spawnTimerMax: " + std::to_string(spawnTimerMax) + "\n";
    //Print the entire string:
    std::cout << info;
    */

    // If spawnTimer reaches spawnTimerMax, we spawn new entities
    if (this->spawnTimer >= spawnTimerMax)
    {
        // Spawn new obstacles
        this->updateObstacles(dt);

        //spawn new coins 
        this->updateCoins(dt);

        // Reset timer
        this->spawnTimer = 0.f;

        //after need to update the collision cf. updateEntitiesandCollision
    }
}

/**
 * @brief Updates game entities and checks for collisions.
 *
 * This function updates the state of game entities and checks for collisions between the player and the entities. 
 * If a collision is detected, the corresponding action is taken (e.g., decrease lives for player, increase score).
 * The function also checks if the entities are out of the window's bounds 
 *
 * If one of the 2 conditions is met, the entity is deleted and the corresponding pointer is removed from the list.
 * 
 * @param dt Time difference since the last frame.
 */
void GameState::updateEntitiesandCollision(const float & dt)
{
    // Update obstacles, coins and check for collisions...
    
    //Update obstacles for player 1
    for (unsigned counter1 = 0; counter1 < this->obstaclesPlayer1.size();)
    {
        auto *obstacle = this->obstaclesPlayer1[counter1];
        obstacle->update(dt); 

        // Check if the obstacle is out of the window
        if (obstacle->getBounds().top > this->window->getSize().y)
        {
            delete obstacle;
            this->obstaclesPlayer1.erase(this->obstaclesPlayer1.begin() + counter1);
            continue; // Skip incrementing the counter
        }
        else if (this->player->getHitboxComponent() != nullptr && obstacle->getHitboxComponent() != nullptr &&
                obstacle->getHitboxComponent()->checkintersects(this->player->getHitboxComponent()->getGlobalBounds()))
        {

            //std::cout << "collision new moi player1" << std::endl;           
            this->player->loseLife();

            delete obstacle;
            this->obstaclesPlayer1.erase(this->obstaclesPlayer1.begin() + counter1);
            continue; // Skip incrementing the counter
        }
        else
        {
            ++counter1;
        }
    }

    // Update obstacles for player 2
    for (unsigned counter2 = 0; counter2 < this->obstaclesPlayer2.size();)
    {
        auto *obstacle = this->obstaclesPlayer2[counter2];
        obstacle->update(dt); 

        // Check if the obstacle is out of the window
        if (obstacle->getBounds().top > this->window->getSize().y)
        {
            delete obstacle;
            this->obstaclesPlayer2.erase(this->obstaclesPlayer2.begin() + counter2);
            continue; // Skip incrementing the counter
        }
        // Check if the obstacle collides with the player 2
        else if (this->player2->getHitboxComponent() != nullptr && obstacle->getHitboxComponent() != nullptr &&
                obstacle->getHitboxComponent()->checkintersects(this->player2->getHitboxComponent()->getGlobalBounds()))
        {
            //std::cout << "collision new moi player2" << std::endl;
            this->player2->loseLife();

            delete obstacle;
            this->obstaclesPlayer2.erase(this->obstaclesPlayer2.begin() + counter2);
            continue; // Skip incrementing the counter
        }
        else
        {
            ++counter2;
        }
    }

    // Update coins and check for collisions...
    // Update coins for player 1
    for (unsigned counter1 = 0; counter1 < this->coinsPlayer1.size();)
    {
        auto *coin = this->coinsPlayer1[counter1];
        coin->update(dt); 

        // Check if the coin is out of the window
        if (coin->getBounds().top > this->window->getSize().y)
        {
            delete coin;
            this->coinsPlayer1.erase(this->coinsPlayer1.begin() + counter1);
            continue; // Skip incrementing the counter
        }
        // Check if the coin collides with the player
        else if (this->player->getHitboxComponent() != nullptr && coin->getHitboxComponent() != nullptr &&
                coin->getHitboxComponent()->checkintersects(this->player->getHitboxComponent()->getGlobalBounds()))
        {
            //std::cout << "coin collision detected player1" << std::endl;
            //Increase player's score
            points1++;

            delete coin;
            this->coinsPlayer1.erase(this->coinsPlayer1.begin() + counter1);
            continue; // Skip incrementing the counter
        }
        else
        {
            ++counter1;
        }
    }

    // Update coins for player 2
    for (unsigned counter2 = 0; counter2 < this->coinsPlayer2.size();)
    {
        auto *coin = this->coinsPlayer2[counter2];
        coin->update(dt); 

        // Check if the coin is out of the window
        if (coin->getBounds().top > this->window->getSize().y)
        {
            delete coin;
            this->coinsPlayer2.erase(this->coinsPlayer2.begin() + counter2);
            continue; // Skip incrementing the counter
        }
        // Check if the coin collides with the player 2
        else if (this->player2->getHitboxComponent() != nullptr && coin->getHitboxComponent() != nullptr &&
                coin->getHitboxComponent()->checkintersects(this->player2->getHitboxComponent()->getGlobalBounds()))
        {
            //std::cout << "coin collision detected player2" << std::endl;
            //Increase player's score
            points2++;
            
            delete coin;
            this->coinsPlayer2.erase(this->coinsPlayer2.begin() + counter2);
            continue; // Skip incrementing the counter
        }
        else
        {
            ++counter2;
        }
    }

}


/**
 * @brief Handles player input and prevents key spamming.
 *
 * This function handles player input, especially movements, and ensures that a cooldown is in place to prevent key spamming.
 *  There are conditions to move the player left, right, up, and down. The function is designed to handle inputs for two players.
 * 
 * @param dt Time difference since the last frame.
 */
//with cooldown so no spamming of the key
void GameState::updatePlayerInput(const float &dt)
{
    // Decrease cooldowns over time
    if (cooldownPlayer1 > 0)
        cooldownPlayer1 -= dt;
    if (cooldownPlayer2 > 0)
        cooldownPlayer2 -= dt;

    //SET POSITION OF THE PLAYER BETWEEN LANE
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        if (cooldownPlayer1 <= 0)
        {
            this->player->movelane(dt, -1.f, 0.f, 1);
            cooldownPlayer1 = cooldownTime;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("2_MOVE_LEFT"))))
    {
        if (cooldownPlayer2 <= 0)
        {
            this->player2->movelane(dt, -1.f, 0.f, 2);
            cooldownPlayer2 = cooldownTime;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        if (cooldownPlayer1 <= 0)
        {
            this->player->movelane(dt, 1.f, 0.f, 1);
            cooldownPlayer1 = cooldownTime;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("2_MOVE_RIGHT"))))
    {
        if (cooldownPlayer2 <= 0)
        {
            this->player2->movelane(dt, 1.f, 0.f, 2);
            cooldownPlayer2 = cooldownTime;
        }
    }

    //SMOOTH MOVEMENT OF THE PLAYER IF UP OR DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->movesmooth(dt, 0.f, -1.f); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("2_MOVE_UP"))))
    {
        this->player2->movesmooth(dt, 0.f, -1.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) 
    {
        this->player->movesmooth(dt, 0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("2_MOVE_DOWN")))) 
    {
        this->player2->movesmooth(dt, 0.f, 1.f);
    }
}


/**
 * @brief Handles general input.
 *
 * This function updates the keytime and checks if the "CLOSE" key has been pressed.
 * If pressed, it pauses or unpauses the game accordingly.
 *
 * @param dt Time difference since the last frame.
 */
void GameState::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) //KEYTIME IMPORTANT
    {
        //so we cant spam echap button
        //std::cout << "GameState::updatePauseInput()"<< "\n";
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

/**
 * @brief Checks game over condition.
 *
 * This function checks if the lives of either player have reached zero, and if so, 
 * it sets the gameover variable to true.
 */
void GameState::updateGameover()
{
    if (this->player->getLives() <= 0 || this->player2->getLives() <= 0)
    {
        this->gameover = true;
    }

}

/**
 * @brief Updates the state of pause menu buttons.
 *
 * This function checks if the "QUIT" button in the pause menu has been pressed, and if so, 
 * ends the state of the game after a small delay.
 */
void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("QUIT") && this->getKeytime())
    {
        // Add delay
        sf::sleep(sf::milliseconds(250)); 
        this->endState();
    }
}

/**
 * @brief Updates the state of gameover menu buttons.
 *
 * This function checks if the "QUIT" button in the game over menu has been pressed, and if so, 
 * ends the state after a delay. Same idea as updatePauseMenuButtons().
 */
void GameState::updateGameoverMenuButtons()
{
    if (this->gameomenu->isButtonPressed("QUIT") && this->getKeytime())
    {
        // Add delay
        sf::sleep(sf::milliseconds(250)); 
        this->endState();
    }
}


/**
 * @brief Main update function for the game state.
 *
 * This function is responsible for updating different parts of the game state 
 * depending on whether the game is paused, over or in progress. 
 * It handles updating mouse positions, keytime, input, player input, entities, and GUI.
 *
 * @param dt Time difference since the last frame.
 */
void GameState::update(const float &dt)
{

    this->updateMousePositions(); 
    this->updateKeytime(dt); //KEYTIME IMPORTANT
    this->updateInput(dt);
    this->updateGameover();

    if (!this->paused && !this->gameover) // Unpaused update and 2 players still alive
    {
        /// std::cout << "GameState::update()" << "\n";
        this->updatePlayerInput(dt); 
        
        this->player->update(dt);
        this->player2->update(dt); 

        this->gui2->updatePlayerScores(this->points1, this->points2);
        this->gui2->updatePlayerLives(this->player->getLives(), this->player2->getLives());

        //this->updateObstacles(dt); //now big method updateEntitiesand...
        this->updateEntitieandSpawn(dt);
        this->updateEntitiesandCollision(dt);

    }
    else if (this->paused) // Paused update
    {
        this->pmenu->update(this->mousePosView);
        // end check is in the pause menu a button is pressed
        this->updatePauseMenuButtons();
    }

    else if (this->gameover)
    {
        //std::cout << "GameState::update() GAMEOVER" << "\n";
        this->gui2->updatePlayerScores(this->points1, this->points2);
        this->gui2->updatePlayerLives(this->player->getLives(), this->player2->getLives());

        this->gameomenu->update(this->mousePosView);
        this->updateGameoverMenuButtons();
        
    }
}

// ----------------------------------------------------------
// Render
// ----------------------------------------------------------
/**
 * @brief Renders game entities.
 *
 * This function is responsible for rendering obstacles and coins in the game. 
 * It renders different sets of entities for player 1 and player 2.
 *
 * @param target The render target to which entities will be rendered.
 */
void GameState::renderEntities(sf::RenderTarget *target)
{

    for (auto *obstacle : this->obstaclesPlayer1)
    {
        obstacle->render(*this->window);
    }

    for (auto *obstacle : this->obstaclesPlayer2)
    {
        obstacle->render(*this->window);
    }

    for (auto *coin : this->coinsPlayer1)
    {
        coin->render(*this->window);
    }

    for (auto *coin : this->coinsPlayer2)
    {
        coin->render(*this->window);
    }


}

/**
 * @brief Renders the game state.
 *
 * This function is responsible for rendering the entire game state. It first checks if the target is valid.
 * If it is, the function draws the background, players, entities, and GUI onto the target.
 * If the game is paused, it renders the pause menu.
 * If the game is over, it sets the winner text based on the remaining lives of the players, 
 * then renders the gameover menu and the winner text.
 *
 * @param target The render target to which the game state will be rendered.
 */
void GameState::render(sf::RenderTarget *target)
{
    if (target)
    {

        target->draw(this->background); 
        
        // Draw the lanes
        //this->window->draw(this->divideLanes);

        this->player->render(*target);
        this->player2->render(*target); 

        // render the entities
        this->renderEntities(target);

        this->gui2->render(target);
    }
    
    if (this->paused) // Pause menu render
    {
        this->pmenu->render(*target);
    }

    // Game Over screen
    //if (this->player->getLives() <= 0 || this->player2->getLives() <= 0)
    if (this->gameover)
    {
        // Set the winner text based on who has no life left
        if (this->player2->getLives() <= 0) 
        {
            winnerText.setString("Player 1 wins");
            this->centerText(winnerText,this->window->getSize().x);
        } 
        else if (this->player->getLives() <= 0) 
        {
            winnerText.setString("Player 2 wins");
            this->centerText(winnerText,this->window->getSize().x);
        } 
        else 
        {
            winnerText.setString("It's a tie!");
            this->centerText(winnerText,this->window->getSize().x);
        }

        this->gui2->render(target); //still update the last lost life of the player to see the last lost
        this->gameomenu->render(*target); //v3 gameoverstate

        // Draw the winner text
        target->draw(winnerText);
    }
}
