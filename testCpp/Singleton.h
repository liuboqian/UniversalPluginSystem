#pragma once
#include <iostream>

class Singleton
{
public:
	static std::shared_ptr<Singleton> Create();
	~Singleton();

private:
	Singleton();
	int a;

};

