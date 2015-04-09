#include <iostream>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int a[1000][1000];
int b[1000][1000];
int c[1000][1000];

int gen()
{
	return rand() % 109;
}

void matrixMul(int beginMat, int endMat, int nn)
{
	for (int i = beginMat; i < endMat; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			for (int k = 0; k < nn; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

int main()
{
	auto start_time = chrono::system_clock::now();
	vector <thread> threads;
	ofstream fout("output.txt");
	int n;
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
	int dist = n / kolThreads;
	for (int i = 0; i < kolThreads; i++)
	{
		threads.push_back(thread(matrixMul,i*dist, min(n, (i + 1)*dist), n));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fout << c[i][j] << ' ';
		}
		fout << endl;
	}
	for (auto& th : threads) th.join();
	auto end_time = chrono::system_clock::now();
	auto dif = end_time - start_time;
	cout << chrono::duration_cast<chrono::milliseconds>(dif).count() << endl;
	return 0;
}