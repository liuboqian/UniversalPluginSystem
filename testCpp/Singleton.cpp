#include "pch.h"
#include "Singleton.h"

using namespace std;

Singleton::Singleton()
{
	cout << "Created" << endl;
}


std::shared_ptr<Singleton>  Singleton::Create()
{
	static shared_ptr<Singleton> _singleton = make_shared<Singleton>(*(new Singleton()));
	return _singleton;
}

Singleton::~Singleton()
{
	cout << "decreated" << endl;
}
