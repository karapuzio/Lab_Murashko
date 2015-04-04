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
	int v[100][100];
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			v[i][j] = 1000000;
		}
	}
	map <pair<string, int>, int> ind;
	int k = 0;
	int kk = 0;
	for (auto it = route.begin(); it != route.end(); it++)
	{
		for (auto jt = (it -> second).begin(); jt != (it -> second).end(); jt++)
		{
			ind.insert(make_pair(make_pair(*jt, kk), k));
			k++;
		}
		kk++;
	}
	kk = 0;
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		for (auto itj = (it -> second).begin(); (++itj) != (it -> second).end(); )
		{
			v[ind[make_pair(*itj,kk)]][ind[make_pair(*(--itj),kk)]] = 1;
			v[ind[make_pair(*itj,kk)]][ind[make_pair(*(++itj),kk)]] = 1;
		}
		kk++;
	}
	int k1 = -1; 
	for (auto it = route.begin(); it != route.end(); ++it)
	{
		k1++;
		int k2 = -1;
		for (auto jt = route.begin(); jt != route.end(); ++jt)
		{
			k2++;
			for (auto iti = (it -> second).begin(); iti != (it -> second).end(); iti++)
			{
				for (auto jtj = (jt -> second).begin(); jtj != (jt -> second).end(); jtj++)
				{
					if (*iti == *jtj)
					{
						auto uk1 = iti;
						auto uk2 = jtj;
						uk1++;
						uk2++;
						if (uk1 == it -> second.end() && uk2 == jt -> second.end())
						{
							continue;
						}
						if (uk1 == it -> second.end())
						{	
							uk1--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							continue;
						}						
						if (uk2 == jt -> second.end())
						{	
							uk2--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							continue;
						}	
						if (*uk1 != *uk2)
						{
							uk2--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							uk2++;
							uk1--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
						}
					}
					if (*iti == *jtj)
					{
						auto uk1 = iti;
						auto uk2 = jtj;
						if (uk1 == it -> second.begin() && uk2 == jt -> second.begin())
						{
							continue;
						}
						if (uk1 == it -> second.begin())
						{	
							uk2--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							continue;
						}						
						if (uk2 == jt -> second.begin())
						{	
							uk1--;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							continue;
						}	
						uk1--; uk2--;
						if (*uk1 != *uk2)
						{
							uk2++;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							uk2--;
							uk1++;
							v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]] = min(3, v[ind[make_pair(*uk2, k2)]][ind[make_pair(*uk1, k1)]]);
							v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]] = min(3, v[ind[make_pair(*uk1, k1)]][ind[make_pair(*uk2, k2)]]);
							}
					}
				}
			}
		}
	}
	int nn = ind.size();
	for (int k = 0; k < nn; k++)
	{
		for (int i = 0; i < nn; i++)
		{
			for (int j = 0; j < nn; j++)
			{
				v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
			}
		}
	}
	int ans = 1000000000;
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			auto g1 = ind.find(make_pair(s1,i));
			auto g2 = ind.find(make_pair(s2,j));
			if (g1 == ind.end() || g2 == ind.end())
			{
				continue;
			}
			ans	= min(ans, v[g1 -> second][g2 -> second]);		
		}
	}
	if (ans == 1000000)
	{
		ans = -1;
	}
	return ans;
}