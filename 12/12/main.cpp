#include <iostream>
#include "MyPretty.h"

using namespace std;

int main()
{
	MyPretty listOlya(320,"GTO","ShamanKing");
	char * name;
	name = listOlya.getFavourite();
	cout << name << endl;
	name = listOlya.getFirst();
	cout << name << endl;
	return 0;
}