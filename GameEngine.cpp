#include "GameEngine.hpp"
#include <iostream>


namespace XQ {

    GameEngine::GameEngine() 
    {
        std::cout << "GameEngine constructor called" << std::endl;
        map = std::make_unique<Map>();
    }
    void GameEngine::init() 
    {
        std::cout << "Init game engine" << std::endl;
    }

    int GameEngine::handleInput()
    {
        std::cout << "what do u what to do?" << std::endl;
        std::cout << "a : move left" << std::endl;
        std::cout << "w: move up" << std::endl;
        std::cout << "d:move right" << std::endl;
        std::cout << "s:move down" << std::endl;
        std::cout << "x:exit" << std::endl;
        char input;
        std::cin >> input;
        if (input == 'x')
            return 0;
        else
            return 1;
    }

    void GameEngine::update() 
    {
        std::cout << "Update game state" << std::endl;
    }

    void GameEngine::render() 
    {
#ifdef _WIN32
        system("cls");
#else
system("clear");
#endif

        std::cout << "Render game" << std::endl;
        map->draw();
        std::cout << static_cast<char>(player->getSymbol());
        for (inti; i < enermies.size(); i++) 
        {
            std::cout << static_cast<char>(enermies[i]->getSymbol());
        }
    }

    void GameEngine::release() 
    {
        std::cout << "Release resources" << std::endl;
    }

}
