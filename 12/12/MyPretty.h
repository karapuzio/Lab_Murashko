class MyPretty
{
private :
	int kolAnime;
	char * favouriteAnime;
	char * firstAnime;
public :
	MyPretty(int ,char *, char *);
	MyPretty(const MyPretty &);
	virtual char * getFavourite();
	char * getFirst();
};