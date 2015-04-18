// В центре окна – текст. При нажатии на клавишу «+» 
// размер шрифта увеличивается, «-» - уменьшается.
// К тексту добавлять каждый раз символы + и –

#undef UNICODE
#include <vector>
#include <algorithm>
#include <windows.h>

//#define WM_CHAT;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "ClassName";
int n ,m;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wcApp;

	// Заполняем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance		= hInstance;   
	wcApp.lpfnWndProc	= WndProc;
	wcApp.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wcApp.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName	= 0;
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style			= CS_HREDRAW | CS_VREDRAW;
	wcApp.cbClsExtra	= 0;
	wcApp.cbWndExtra	= 0;
	
	// Регистрируем класс окна
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hWnd=CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

//	sscanf(lpCmdLine, "%d%d", &n, &m);
	while (GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	static HDC hdc;
	static char s[2000] = "Hello";
	PAINTSTRUCT ps;
	static int size = 12;

	static unsigned int key;
	
	switch (uMsg) {

	case WM_CREATE: 
		{
		hdc = GetDC(hWnd);
		break; 
		}
	case WM_PAINT:
		{
		// drawing code
		hdc=BeginPaint(hWnd,&ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		HFONT hFont = CreateFont(size, 0,0,0, 400, 0,0,0, DEFAULT_CHARSET, 0,0,0,0,0);
		SelectObject(hdc, hFont);
		DrawText(hdc,s, strlen(s), &rect, DT_CENTER| DT_VCENTER | DT_SINGLELINE);
	//	TextOut(hdc, 100,100, s, strlen(s));
		DeleteObject(hFont);
		break;
		}
	case WM_CHAR:
	{
		key = wParam;
		if (wParam != VK_BACK)
		{
			s[strlen(s)] = wParam;
		}
		switch(key) {
		case VK_BACK:
			s[strlen(s) - 1] = 0;
			break;
		case 45:
			if (size - 3 > 0)
			{
				size -= 3;
			}
			break;
		case 43:
			size += 3;
			break;
		break;
		} 
		InvalidateRect(hWnd, NULL, true);
		break;
	}
	case WM_DESTROY:
		{
		PostQuitMessage(0);
		break;
		}
	default:
		return (DefWindowProc(hWnd,uMsg,wParam,lParam));
	}
	return (0);
}
