//Вывести текст в четырех углах и в центре клиентской области.
//Нарисуйте эллипс, вписанный в клиентскую область окна.
//Нарисуйте прямоугольник, границы которого находятся на расстоянии фиксированного количества пикселей от границ клиентской области окна.

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
		double x = rect.right;
		double y = rect.bottom;
		Rectangle(hdc, 2 ,2, x - 2, y - 2);
		Ellipse(hdc, 0, 0, x, y);
		DrawText(hdc,s, strlen(s), &rect, DT_CENTER| DT_VCENTER | DT_SINGLELINE);
		DrawText(hdc,s, strlen(s), &rect, DT_BOTTOM| DT_LEFT | DT_SINGLELINE);
		DrawText(hdc,s, strlen(s), &rect, DT_BOTTOM| DT_RIGHT | DT_SINGLELINE);
		DrawText(hdc,s, strlen(s), &rect, DT_TOP| DT_LEFT | DT_SINGLELINE);
		DrawText(hdc,s, strlen(s), &rect, DT_TOP| DT_RIGHT | DT_SINGLELINE);
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
