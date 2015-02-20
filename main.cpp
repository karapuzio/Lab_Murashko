#include <iostream>

using namespace std;

int main()
{
    bool prime[100000];
    int n;
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		prime[i] = true;
	}
	prime[0] = prime[1] = false;
	for (int i = 0; i < n; i++)
	{
		if (prime[i] && (i * i < n))
		{
			for (int j = i*i; j < n; j+=i)
			{
				prime[j] = false;
			}
		}
	}
	for (int i = 2; i < n; i++)
	{
		if (prime[i])
		{
			cout << i << endl;
		}
	}
	return 0;
}