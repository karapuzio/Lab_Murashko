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

int ** matA;
int ** matB;
int ** matC;
int n;

mutex mtx;

int gen()
{
	random_device rd;
	uniform_int_distribution<int> uid(0, 100000);
	return uid(rd);
}

void matrixMul(int cur)
{
	int * matD = new int[n];
	for (int i = 0; i < n; i++)
	{
		matD[i] = 0;
	}
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{
			matD[j] += matA[cur][k] * matB[k][j];
		}
	}
	unique_lock<mutex> lock(mtx);
	for (int i = 0; i < n; i++)
	{

		matC[cur][i] = matD[i];
	}
	lock.unlock();
}

int main()
{
	vector <thread> threads;
	ofstream fout("output.txt");
	cin >> n;
	matA = new int * [n];
	matB = new int * [n];
	matC = new int * [n];
	for (int i = 0; i<n; ++i)
	{
		matA[i] = new int[n];
		matB[i] = new int[n];
		matC[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matA[i][j] = gen();
			matB[i][j] = gen();
			matC[i][j] = 0;
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
				if (threads.size() <= j)
				{
					threads.push_back(thread(matrixMul, i));
					uk[j] = i;
					j++;
					f = false;
					continue;
				}
				if (matC[uk[j]][n-1] != 0)
				{
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
			fout << matC[i][j] << ' ';
		}
		fout << endl;
	}
	auto end_time = chrono::system_clock::now();
	auto dif = end_time - start_time;
	cout << chrono::duration_cast<chrono::milliseconds>(dif).count() << endl;
	return 0;
}