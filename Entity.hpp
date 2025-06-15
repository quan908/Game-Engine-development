#pragma once
namespace XQ
{
	class Entity 
	{
	protected:
		int posX;
		int posY;
		char symbol;
	public:
		int getX() const;
		int getY() const;
		int getSymbol() const;
	};
};

