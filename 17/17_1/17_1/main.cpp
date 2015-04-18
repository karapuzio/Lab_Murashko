// Разработать приложение так, чтобы в окне было изображено 
// несколько (десятков)прямоугольников разных цветов.

#undef UNICODE
#include <vector>
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
	static HDC hDC;
	HDC hdc;
	static HBRUSH hOldBrush, hBrush; 
	static double x1, y1, x2, y2, k1, k2;
	static COLORREF cr;

	switch (uMsg) 
	{ 
	case WM_CREATE:
		{
		break;
		}

	case WM_PAINT: 
		PAINTSTRUCT ps; 
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		RECT curRect;
		x1 = 0; y1 = 0;
		x2 = rect.right;
		y2 = rect.bottom;
		k1 = rect.right / 150;
		k2 = rect.bottom / 100;
		for (int i = 0; i < 50; ++i) 
		{ 
			cr = RGB(0 + 30 * i, 20 + 3 * i, 40);
			hBrush=CreateSolidBrush(cr);
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			curRect.left = x1 + i * k1;
			curRect.top = y1 + i * k2;
			curRect.right = x2 - i * k1; 
			curRect.bottom = y2 - i *k2;
			FillRect(hdc, &curRect, hBrush); 
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush);
		} 

		EndPaint(hWnd, &ps); 
		break; 

	case WM_DESTROY: 
		{
		PostQuitMessage(0); 
		break; 
		}

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); 
	} 
	return 0; 
} 


