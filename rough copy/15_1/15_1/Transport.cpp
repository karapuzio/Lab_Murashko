#include "Transport.h"

void Transport :: addRoute(int number, int kind, list<string> :: const_iterator itBegin, list<string> :: const_iterator itEnd)
{
	list <string> curList;
	for (auto it = itBegin; it != itEnd; ++it)
	{
		curList.push_back(*it);
	}
	for (auto it = curList.begin(); it != curList.end(); ++it)
	{
		stops[*it]++;
	}
	route.insert(make_pair(make_pair (number, kind), curList));
}

void Transport :: deleteRoute(int number, int kind)
{
	route.erase(make_pair(number, kind));
}

void Transport :: addStop(string newStop)
{
	stops.insert(make_pair(newStop,0));
}

void Transport :: deleteStop(string oldStop)
{
	stops.erase(oldStop);
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		(it -> second).erase(find((it -> second).begin(), (it -> second.end()), oldStop));
		if (it -> second.size() == 0)
		{
			deleteRoute(it -> first.first, it -> first.second);
		}
	}
}

int Transport :: getCountRouts()
{
	return route.size();
}

int Transport :: getCountStops()
{
	return stops.size();
}

pair<int *, int *> Transport :: listRoute(string curStop) 
{
	while (routesList.size() != 0)
	{
		routesList.pop_back();
	}
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		auto itCur = find((it -> second).begin(), (it -> second.end()), curStop);
		if (itCur != it -> second.end())
		{
			routesList.push_back(it -> first.first);
		}
	}
	int * a = &routesList[0];
	return make_pair(&routesList[0], &routesList[routesList.size()-1]);
}

pair<int *, int *> Transport :: listRouteKind(int curKind, int minNumber, int maxNumber) 
{
	while (routesList.size() != 0)
	{
		routesList.pop_back();
	}
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		if (it -> first.second == curKind && it -> first.first >= minNumber && it -> first.first <= maxNumber)
		{
			routesList.push_back(it -> first.first);
		}
	}
	return make_pair(&routesList[0], &routesList[routesList.size()-1]);
}

pair<string *, string *> Transport :: listStopsNotUse()
{
	while (stopsList.size() != 0)
	{
		stopsList.pop_back();
	}
	for (auto it = stops.begin(); it != stops.end(); ++it)
	{
		if (it -> second == 0)
		{
			stopsList.push_back(it -> first);
		}
	}
	return make_pair(&stopsList[0], &stopsList[stopsList.size()-1]);
}

string Transport :: maxTrafficStop()
{
	int max = 0;
	string uk= "";
	for (auto it = stops.begin(); it != stops.end(); ++it)
	{
		if (it -> second > max)
		{
			max = it -> second;
			uk = it -> first;
		}
	}
	return uk;
}

int Transport :: floyd(string s1, string s2)
{
	map <string, int> ind;
	int k = 0;
	for (auto it = stops.begin(); it != stops.end(); it++)
	{
		
		ind.insert(make_pair(it -> first, k));
		k++;
	}
	int nn = ind.size();
	vector< vector< pair<int, int>>> v(nn);
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		for (auto itj = (it -> second).begin(); (++itj) != (it -> second).end(); )
		{
			v[ind[*(--itj)]].push_back(make_pair(ind[*(itj)],1));
			v[ind[*(++itj)]].push_back(make_pair(ind[*(itj)],1));
		}
	}
	int ans;
	vector <int> d(nn, 1000000);
	int s = ind[s1];
	d[s] = 0;
	set <pair<int, int>> q;
	q.insert(make_pair(d[s], s));
	while (!q.empty())
	{
		int vv = q.begin() -> second;
		q.erase(q.begin());
		for (int i = 0; i < v[vv].size(); i++)
		{
			int next = v[vv][i].first;
			int cost = v[vv][i].second;
			if (d[vv] + cost < d[next])
			{
				q.erase(make_pair(d[next],next));
				d[next] = d[vv] + cost;
				q.insert(make_pair(d[next], next));
			}
		}
	}
	ans = d[ind[s2]];
	/*vector <int> change(nn, nn+1);
	change[ind[s1]] = -1;
	for (int i = -1; i < nn; i++)
	{
		for (auto it = route.begin(); it != route.end(); it++)
		{
			bool f = false;
			for (auto jt = it -> second.begin(); jt != it -> second.end(); jt++)
			{
				if (change[ind[*jt]] == i)
				{
					f = true;
				}
			}
			if (!f)
			{
				continue;
			}
			for (auto jt = it -> second.begin(); jt != it -> second.end(); jt++)
			{
				if (change[ind[*jt]] > i + 1)
				{
					change[ind[*jt]] = i + 1;
				}
			}
		}
	if (ans == 1000000)
	{
		ans = -1;
	}
	if (ans != -1)
	{
		ans += change[ind[s2]]*3;
	}
	return ans;
	}*/

	if (ans == 1000000)
	{
		return -1;
	}
	vector <vector <pair <int, int>>> buf(100);
	for (auto it = route.begin(); it != route.end(); it++)
	{
		for (auto jt = it -> second.begin(); jt != it -> second.end(); jt++)
		{
			buf[ind[*jt]].push_back(make_pair(it -> first.first, it -> first.second)); 
		}
	}
	vector <pair <int, int>> karma1;
	vector <int> karma2;
	bool prov[100][100];
	vector <bool> proverka (nn, false);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			prov[i][j] = false;
		}
	}
	for (int i = 0; i < buf[ind[s1]].size(); i++)
	{
		karma1.push_back(make_pair(buf[ind[s1]][i].first, buf[ind[s1]][i].second));
		karma2.push_back(0);
		prov[buf[ind[s1]][i].first][buf[ind[s1]][i].second] = true;
	}
	proverka[ind[s1]] = true;
	vector <int> rain(100, 10000);
	k = 0;
	auto i = karma1.begin();
	auto t = karma1.size();
	while (i != karma1.end())
	{
		prov[i -> first][i -> second] = true;
		list <string> lll = route[*i];
		for (auto j = lll.begin(); j != lll.end(); j++)
		{
			rain[ind[*j]] = min(rain[ind[*j]], karma2[k]);
		}
		k++;
		while (k == t)
		{
			int min = 10000;
			int uk = 0;
			for (int j = 0; j < nn; j++)
			{
				if (min > rain[j] && proverka[j] == false)
				{
					min = rain[j];
					uk = j;
				}
			}
			proverka[uk] = true;
			for (int j = 0; j < buf[uk].size(); j++)
			{
				if (prov[buf[uk][j].first][buf[uk][j].second] == true)
				{
					continue;
				}
				karma1.push_back(make_pair(buf[uk][j].first, buf[uk][j].second));
				karma2.push_back(min+1);
			}
			t = karma1.size();
		}
		i++;
	}
	int kol = rain[ind[s2]];
	for (int i = 0; i < buf[ind[s2]].size(); i++)
	{
	}
	ans += kol*3;
	return ans;
}