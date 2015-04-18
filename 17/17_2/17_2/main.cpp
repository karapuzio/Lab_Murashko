// Светофор. Обеспечить переключение цветов.

#undef UNICODE
#include <vector>
#include <cmath>
#include <algorithm>
#include <windows.h>

using namespace std;

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

	while (GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	HDC hdc;
	PAINTSTRUCT ps;
	static int sec;
	static bool f = true;
	static unsigned int key;
	static HBRUSH hOldBrush, hBrush;
	static COLORREF cr;

	switch (uMsg) {

	case WM_CREATE: 
		{
		SetTimer(hWnd, 33, 1000, NULL);
		break; 
		}

	case WM_TIMER:
		{
			sec++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

	case WM_PAINT:
		{
		// drawing code
		hdc=BeginPaint(hWnd,&ps);
		RECT rect;
		GetClientRect(hWnd, &rect);

		double xc = rect.right/2;
		double yc = rect.bottom/2;
		
		double xxc = rect.right/5;
		double yyc = (rect.bottom - 20) / 13;

		cr = RGB(95, 95, 95);
		hBrush=CreateSolidBrush(cr);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, xxc * 2, 1, xxc * 3, rect.bottom - 1);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

		cr = RGB(128, 0, 0);
		if (sec % 4 == 1)
		{
			cr = RGB(255, 0, 0);
		}
		hBrush=CreateSolidBrush(cr);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		double smes;
		smes = xxc / 7;
		Ellipse(hdc, xxc * 2 + smes, 10 + yyc , xxc * 3 - smes, 10 + yyc*4 );
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

		cr = RGB(170, 170, 47);
		if (sec % 2 == 0)
		{
			cr = RGB(255, 255, 0);
		}
		hBrush=CreateSolidBrush(cr);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, xxc * 2 + smes, 10 + yyc*5 , xxc * 3 - smes, 10 + yyc*8 );
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

		cr = RGB(0, 128, 0);
		if (sec % 4 == 3)
		{
			cr = RGB(0, 255, 0);
		}
		hBrush=CreateSolidBrush(cr);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, xxc * 2 + smes, 10 + yyc*9, xxc * 3 - smes, 10 + yyc*12 );
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);		

		EndPaint(hWnd, &ps);
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
