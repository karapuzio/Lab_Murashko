#include <iostream>

using namespace std;

int strLength(char * s)
{
	int res = 0;
	_asm
	{
		cld
		mov edi, s
		mov esi, edi
		mov ecx, 0ffffffffh
		xor al, al
		repne scasb 
		sub edi, esi
		dec edi
		mov res, edi
	}
	return res;
}

int main()
{
	char s[1000];
	cin.getline(s,1000);
	int d = strLength(s);
	int ans = 0;
	__asm
	{

		cld
		mov ebx, d
		mov al, ' '
		lea edi, s
		mov ecx, d
foor :
		or al, 0 ; reset zf
		repne scasb
		jz found
		jecxz endd
		jmp foor
found :
		sub ebx, ecx
		cmp ebx, ans
		jg change
		mov ebx, ecx
		jmp foor
change :
		mov ans, ebx
		mov ebx, ecx
		jmp foor
endd :
		inc ebx
		cmp ebx, ans
		jg you
		jmp kon
you:
		mov ans, ebx
kon:
	}
	cout << ans-1 << endl;
	return 0;
}


