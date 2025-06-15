#pragma once
#include<vector>
namespace XQ
{
	class Map
	{
	public:
		Map();
		void draw();
	private:
		char titles[20][20];
		const unsigned int width = 20;
		const unsigned int height = 20;
		std::vector< std::vector<char>>tiles;
	};
}

