// В центре окна – окружность, в центре которой - число, равное количеству секунд, 
// прошедших от момента запуска приложения. Это наши часы. Заставьте их «тикать» через 1 секунду. 
// Часы можно остановить(клавиша «-»), снова запустить (клавиша «+») или запустить заново (клавиши «Ctrl+S»).

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

	switch (uMsg) {

	case WM_CREATE: 
		{
		SetTimer(hWnd, 33, 1000, NULL);
		break; 
		}

	case WM_TIMER:
		{
			if (f)
			{
				sec++;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}

	case WM_CHAR:
		{
		key = wParam; //Получаем код нажатой клавиши
		//Обработка нажатия клавиш
		switch(key) {
		case 19:
			sec = 0;
			break;
		case 45:
			f = false;
			break;
		case 43:
			f = true;
			break;
		} 
		break;
		}

	case WM_PAINT:
		{
		// drawing code
		hdc=BeginPaint(hWnd,&ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		char buffer[20];
		sprintf(buffer,"%d",sec);
		double xc = rect.right/2;
		double yc = rect.bottom/2;
		Ellipse(hdc, xc - 90, yc + 90, xc + 90, yc - 90);
		TextOut(hdc,xc,yc,buffer,strlen(buffer));
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
