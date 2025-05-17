#include<iostream>
#include<cassert>
#include "Dog.hpp"
using namespace std;
void makeSay(Dog& d)
{
	d.say();
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::string s = "hello this isa string";
	std::string s2 = "hello this is string2";
	s = s2;
	std::string s3 = s + s2;

	
	Dog* p_d1 = new Dog("Mark");
	makeSay(*p_d1); 
	delete p_d1;
		//Dog d = Dog();//constructor is called	
		//Dog d2 = d;//copy constructor is called
		//Dog d3(d);// copy constructor is called
		//d2 = d3;//=operator is called

		//Dog* p_d1 = new Dog();// constrctor is called
		//Dog* p_d2 = new Dog(*p_d1);
		//p_d1->say();
		//p_d2->say();
		//*p_d1 = *p_d2; //oprator is called
		//how canI use constructor
		//how can I use operator
		//delete p_d1;//deconstrcotr is calld
		//delete p_d2;

		//p_d->say();
		//(*p_d).say();// dont use this way,not professional
		//delete p_d;

	assert((_CrtCheckMemory));
	_CrtDumpMemoryLeaks();


}