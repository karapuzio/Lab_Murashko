#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "Transport.h"

using namespace std;

int main()
{
	ifstream fin("input.txt");
	Transport Gomel;
	int n;
	int a[100];
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		int num, ki;
		fin >> num >> ki;
		list <string> cur;
		for (int j = 0; j < a[i]; j++)
		{
			string ss;
			fin >> ss;
			cur.push_back(ss);
		}
		Gomel.addRoute(num, ki, cur.begin(), cur.end());
	}
//	cout << "Distanse" << Gomel.floyd("Lenina", "Kirova") << endl;
	cout << Gomel.getCountRouts() << endl;
	cout << Gomel.getCountStops() << endl;
	cout << Gomel.maxTrafficStop() << endl;
	Gomel.deleteRoute(17, 2);
	Gomel.deleteRoute(20, 3);
	Gomel.deleteStop("sosnovaya");
	Gomel.addStop("borykina");
	Gomel.addStop("kosareva");
	cout << Gomel.maxTrafficStop() << endl;
	cout << Gomel.getCountRouts() << endl;
	cout << Gomel.getCountStops() << endl;
	auto s = Gomel.listRoute("lenina");
	for (auto i = s.first; i<= s.second; i++)
	{
		cout << *i << endl;
	}
	s = Gomel.listRouteKind(1,1,30);
	for (auto i = s.first; i <= s.second; ++i)
	{
		cout << *i << endl;
	}
	auto ss = Gomel.listStopsNotUse();
	for (auto i = ss.first; i <= ss.second; ++i)
	{
		cout << *i << endl;
	}
	return 0;
}