#include<iostream>
#include<memory>
#include "GameEngine.hpp"
#include"Map.hpp"
using namespace XQ;
int main()
{
	std::unique_ptr<GameEngine> gameEngine = std::make_unique< GameEngine>();
	gameEngine->init();
	while (true)
	{


		char choice = gameEngine->handleInput();
		if (choice == 0)
			break;
			gameEngine->update();
			gameEngine->render();
	}

	gameEngine->release();
	
	
	return 0;
}