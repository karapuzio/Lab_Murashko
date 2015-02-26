#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

template <class T>
void swapMaxMin(T & container)
{
	auto p = container.begin();
	auto min = *p;
	auto max = *p;
	auto ukMax = p;
	auto ukMin = p;
	for (auto p = container.begin(); p != container.end(); ++p)
	{
		if (*p > max)
		{
			max = (*p);
			ukMax = p;
		}
		if (*p < min)
		{
			min = (*p);
			ukMin = p;
		}
	}
	*(ukMax) = min;
	*(ukMin) = max;
}

int main()
{
	vector <string> container1(10, "abacaba");
	list <double> container2(5, 3.5);
	auto p = container1.begin();
	*(p + 8) = "abacab";
	*(p +2) = "abacad";
	swapMaxMin(container1);
	swapMaxMin(container2);
	for (auto p = container1.begin(); p != container1. end(); ++p)
	{
		cout << *p << endl;
	}
	for (auto p = container2.begin(); p != container2.end(); ++p)
	{
		cout << *p << endl;
	}
}