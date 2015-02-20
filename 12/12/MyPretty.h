class MyPretty
{
protected :
	int kolAnime;
	char * favouriteAnime;
	char * firstAnime;
public :
	MyPretty(int , char *, char *);
	MyPretty(const MyPretty &);
	virtual char * getFavourite();
	char * getFirst();
};

class MyPrettyAnimanga : public MyPretty
{
private :
	char * favouriteManga;
	char * firstManga;
public :
	MyPrettyAnimanga(int, char *, char *, char *, char *);
	char * getFavourite();
};