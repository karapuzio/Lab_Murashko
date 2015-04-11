#include <iostream>
#include <fstream>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int a[10000][10000];
int b[10000][10000];
int c[10000][10000];
int n;

mutex mtx;

int gen()
{
	return rand() % 109;
}

void matrixMul(int cur)
{
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{
		//	unique_lock<mutex> lck(mtx, defer_lock);
			//lck.lock();
			c[cur][j] += a[cur][k] * b[k][j];
		//	lck.unlock();
		}
	}
}

int main()
{
	vector <thread> threads;
	ofstream fout("output.txt");
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = gen();
			b[i][j] = gen();
		}
	}
	int kolThreads;
	cin >> kolThreads;
	auto start_time = chrono::system_clock::now();
	int dist = n / kolThreads;
	int uk[100000];
	for (int i = 0; i < n; i++)
	{
		bool f = true;
		while (f)
		{
			int j = 0;
			while (j < kolThreads)
			{
				if (threads.size() <= j || c[uk[j]][n-1] != 0)
				{
					threads.push_back(thread(matrixMul, i));
					uk[j] = i;
					j++;
					f = false;
					continue;
				}
				j++;
			}
		}
	}
	for (auto& th : threads) th.join();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fout << c[i][j] << ' ';
		}
		fout << endl;
	}
	auto end_time = chrono::system_clock::now();
	auto dif = end_time - start_time;
	cout << chrono::duration_cast<chrono::milliseconds>(dif).count() << endl;
	return 0;
}