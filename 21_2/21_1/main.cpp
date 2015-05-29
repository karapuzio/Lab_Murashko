#include <iostream>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	int a[1000];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i*m+j];
		}
	}
	int anss[1000];
	int ans = 0;
	int kol = 0;

	__asm
	{
		mov eax, m
		mul n
		mov edi, eax
		mov eax, 0
		dec eax
	//	xor edx, edx
		mov ecx, m
		xor ebx, ebx
foor:
		inc eax
		cmp ecx, 0
		je endd
		dec ecx
		cmp ebx, ans
		jg swaap
		jmp nu
swaap:
		mov ans, ebx
nu:
		mov edx, eax
		xor ebx, ebx
sum: 
		add ebx, a[edx*4]
		add edx, m
		cmp edx, edi
		jge foor
		jmp sum

endd:
		cmp ebx, ans
		jg great
		jmp kon
great:
		mov ans, ebx
		jmp kon
kon:


		mov eax, m
		mul n
		mov edi, eax
		mov eax, 0
		dec eax
	//	xor edx, edx
		mov ecx, m
		xor ebx, ebx
		xor esi, esi
fooor:
		inc eax
		cmp ecx, 0
		je enddd
		dec ecx
		cmp ebx, ans
		je swaaap
		jmp nuu
swaaap:
		mov anss[esi*4], eax
		inc esi
nuu:
		mov edx, eax
		xor ebx, ebx
suum: 
		add ebx, a[edx*4]
		add edx, m
		cmp edx, edi
		jge fooor
		jmp suum
enddd:
		cmp ebx, ans
		je greeat
		jmp koon
greeat:
		mov anss[esi*4], eax
		inc esi
koon:
		mov kol, esi
	}
//	cout << ans << endl;
	for(int i = 0; i < kol; i++)
	{
		cout << anss[i] << endl;
	}
	return 0;
}