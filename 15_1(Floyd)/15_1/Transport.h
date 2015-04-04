#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Transport
{
private :
	map <pair<int, int>, list <string> > route; 
	map <string, int> stops;
	vector <int> routesList;
	vector <string> stopsList;
public :
	void addRoute(int, int, list <string> :: const_iterator, list <string> :: const_iterator);	
	void deleteRoute(int, int);
	void addStop(string);
	void deleteStop(string);
	int getCountRouts();
	int getCountStops();
	pair<int *, int *> listRoute(string);
	pair<int *, int *> listRouteKind(int, int, int);
	pair<string *, string *> listStopsNotUse();
	string maxTrafficStop();
	int floyd(string, string);
};
