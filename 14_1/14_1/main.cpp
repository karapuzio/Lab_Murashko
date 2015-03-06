#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct nameLine
{
	string nameStr;
	int nameInt;
};

bool swapEl(const nameLine & a, const nameLine & b)
{
	if (a.nameStr < b.nameStr)
	{
		return true;
	}
	if (a.nameStr > b.nameStr)
	{
		return false;
	}
	if (a.nameInt < b.nameInt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, string argv[])
{
	/*ifstream fin("input.txt");
	int argc;
	string argv[1000];
	fin >> argc;
	for (int i = 0; i < argc; i++)
	{
		fin >> argv[i];
	}*/
	vector <nameLine> totalStr;
	for (int i = 0; i < argc; i++)
	{
		auto d = argv[i].length();
		int ch = 0;
		int st = 1;
		int kk = d+1;
		for (int j = d-1; j > -1; j--)
		{
			kk--;
			if (argv[i][j] > 47 && argv[i][j] < 58)
			{
				ch = ch + (argv[i][j]-48) * st;
				st *= 10;
			}
			else 
			{
				break;
			}
		}
		nameLine promStr;
		if (kk == d)
		{
			ch = -1;
		}
		promStr.nameInt = ch;
		for (int k = 0; k < kk; k++)
		{
			promStr.nameStr += argv[i][k];
		}
		totalStr.push_back(promStr);
	}
	sort(totalStr.begin(), totalStr.end(), swapEl);
	for (auto p = totalStr.begin(); p != totalStr.end(); ++p)
	{
		cout << p -> nameStr;
		if (p -> nameInt > -1)
		{
			cout << p -> nameInt;
		}
		cout << endl;
	}
	return 0;
}