#include "Entity.hpp"
namespace XQ
{
	Entity::Entity() :posX(0), posY(0), symbol('X') 
	{
		Entity::Entity(int x, int y, char symbol)
	}
	int Entity::getX() const 
	{
		return posX;
	}
	int Entity::getY() const
	{
		return posY;
	}
	int Entity::getSymbol() const
	{
		return symbol;
	}
}
