#include "Dog.hpp"
#include<iostream>
#include<cstring>
using namespace std;
Dog::Dog(const char *_name)
{
	name = new char[10];
	strcpy_s(name,10,_name);
}
Dog::Dog()
{
	name = new char[10];
	
}
Dog::Dog(const Dog&other)
{
	//deep copy
	cout << "copy constructor is called.\n";
	name = new char[10];
	for (int i = 0; i < 10; i++)
	{
		name[i] = other.name[i];
	}
}
Dog& Dog::operator = (const Dog& other)
{
	cout << "operator is called.\n";
	name = new char[10];
	for (int i = 0; i < 10; i++)
	{
		name[i] = other.name[i];
	}
	return *this;
}
Dog::~Dog()
{
	delete[]name;

}
void Dog::say()
{
	cout << "Hong!" << endl;

}
