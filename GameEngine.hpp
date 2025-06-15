#pragma once
#include"Map.hpp"
#include<memory>
#include"Player.hpp"
#include"Enermy.hpp"
namespace XQ
{
	class GameEngine 
	{
	public:
		GameEngine();
		void init();
		int handleInput();
		void update();
		void render();
		void release();
	private:
		std::unique_ptr<Map> map;
		std::unique_ptr<Player>Player;
		std::vector<std::shared_ptr<Enermy>>enermies;
	};
};

