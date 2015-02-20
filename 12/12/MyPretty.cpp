#include "MyPretty.h"

MyPretty :: MyPretty(int n, char * name1, char * name2)
{
	kolAnime = n;
	favouriteAnime = name1;
	firstAnime = name2;
}

MyPretty :: MyPretty(const MyPretty & list)
{
	kolAnime = list.kolAnime;
	favouriteAnime = list.favouriteAnime;
	firstAnime = list.firstAnime;
}

char * MyPretty :: getFavourite()
{
	return favouriteAnime;
}

char * MyPretty :: getFirst()
{
	return firstAnime;
}