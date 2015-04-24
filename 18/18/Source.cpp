#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{ 
	int a;
	int b;
	int gcd;
	int result;
	cin >> a >> b;

	__asm
	{
		mov eax, a
		mov ebx, b
	for1:
		cmp eax, ebx
		je metka_equal
		jl metka_less
		sub eax, ebx
		jmp for1
	metka_less:
		sub ebx, eax
		jmp for1
	metka_equal:
		mov gcd, eax

		mov eax, a
		mul b
		cdq
		idiv gcd

		mov result, eax
	}
	cout << result << endl;
	return 0;
}