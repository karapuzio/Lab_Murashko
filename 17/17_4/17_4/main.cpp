//ѕрограмма ЂЎарикиї - на месте щелчка левой клавишей мыши по€вл€етс€ окружность 
// начального размера. ѕри повторных щелчках внутри окружности ее диаметр 
// увеличиваетс€ на фиксированную величину, вне окружности Ц рисуем новую. 
// ќбеспечить отображение всех окружностей при сворачивании/разворачивании окна 
//(хранить координаты щелчков мыши).

#undef UNICODE
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cmath>

using namespace std;

struct Point { 
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {} 
	int x; 
	int y;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "ClassName";
int n ,m;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wcApp;

	// «аполн€ем структуру класса окна 
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
	
// –егистрируем класс окна
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
	static HDC hdc;
	static HBRUSH hOldBrush, hBrush; 
	static int x, y;
	static vector <Point> curve; 
	static vector <int> rad;
	unsigned int key;
	static int session = 1;
	static vector<COLORREF> col;
	static COLORREF cr;
	static int uk;

	switch (uMsg) 
	{ 
	case WM_CREATE: 
		hDC = GetDC(hWnd);
		break; 

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam); 
		y = HIWORD(lParam); 
		uk = -1;
		for (int i =0; i < curve.size(); ++i) 
		{
			Point it = curve[i];
			if (pow((it.x - x)*(it.x - x) + (it.y - y)*(it.y - y), 0.5) <= rad[i])
			{
				uk = i;
			}
		}
		if (uk == -1)
		{
			cr = RGB(rand() % 256,rand() % 256, rand() % 256);
			col.push_back(cr);
			hBrush=CreateSolidBrush(cr);
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			x = LOWORD(lParam); 
			Ellipse(hDC, x - 50, y + 50, x + 50, y - 50);
			curve.push_back(Point(x, y)); 
			col.push_back(cr);
			rad.push_back(50);
		}
		else
		{
			rad[uk] += 10;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_PAINT: 
		PAINTSTRUCT ps; 
		hdc = BeginPaint(hWnd, &ps);
		for (int i =0; i < curve.size(); ++i) { 
			cr = col[i];
			Point it = curve[i];
			hBrush=CreateSolidBrush(cr);
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, it.x - rad[i], it.y + rad[i], it.x + rad[i], it.y - rad[i]);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush);
		} 

		EndPaint(hWnd, &ps); 
		break; 

	case WM_DESTROY: 
		ReleaseDC(hWnd, hDC); 
		PostQuitMessage(0); 
		break; 

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); 
	} 
	return 0; 
} 


