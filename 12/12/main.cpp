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

	MyPrettyAnimanga listAndrey(56, "Naruto", "Laputa", "Blame", "Clannad");
	name = listAndrey.getFavourite();
	cout << name << endl;
	name = listAndrey.getFirst();
	cout << name << endl;

	return 0;
}