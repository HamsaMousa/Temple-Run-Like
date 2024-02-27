#include "GeneInc.hpp"
#include"Game.hpp"


int main()
{

	//Game game;
	Game& game = Game::getInstance();
	
	game.run();

	return 0;
}