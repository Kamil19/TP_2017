// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include "queue"

#define MAX_LOADSTRING 100
#define TMR_1 1
#define ID_P1K2 11
#define ID_P1K3 12
#define ID_P2K1 13
#define ID_P2K3 14
#define ID_P3K1 15
#define ID_P3K2 16

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

struct czlowiek
{
	int pocz;
	int konc;
};

queue <czlowiek> pentro1;
queue <czlowiek> pentro2;
queue <czlowiek> pentro3;
queue <czlowiek> winda;

void rysuj_pentro(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen1(Color(255, 100, 100, 255));
	Pen pen2(Color(100, 255, 100, 255));
	Pen pen3(Color(100, 100, 255, 255));


	graphics.DrawRectangle(&pen1, 5, 5, 200, 450);									//rysowanie szybu windy
	graphics.DrawRectangle(&pen1, 205, 5, 200, 150);									//rysowanie piêter
	graphics.DrawRectangle(&pen2, 205, 155, 200, 150);
	graphics.DrawRectangle(&pen3, 205, 305, 200, 150);
}






void portret(HDC hdc)											//rysowanie ludzi czekajacych na piêtrze
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 128, 128, 255));
	for (int p = 1; p <= 3; p++)
	{
		if (p = 1)
		{
			for (int k = 0; k < pentro1.size(); k++)
			{
				graphics.DrawRectangle(&pen, 220 + k * 30, 380, 20, 60);
			}
		};
		if (p = 2)
		{
			for (int k = 0; k < pentro2.size(); k++)
			{
				graphics.DrawRectangle(&pen, 220 + k * 30, 230, 20, 60);
			}
		};
		if (p = 3)
		{
			for (int k = 0; k < pentro3.size(); k++)
			{
				graphics.DrawRectangle(&pen, 220 + k * 30, 80, 20, 60);
			}
		};
	}

}

void wybielanie_ludzi(HWND hWnd, HDC hdc, int poz_windy)	//czyszczenie piêter po uchodŸcach
{
	RECT drawArea = { 205, poz_windy, 500, poz_windy + 150 };
	InvalidateRect(hWnd, &drawArea, TRUE);
}

void dzielostworzenia(HWND hWnd, int a, int b)				//umieszczanie cz³owieka na odpowiednim piêtrze
{
	HDC hdc = GetDC(hWnd);
	czlowiek kobieta;
	kobieta.pocz = a;
	kobieta.konc = b;
	if (a == 1)
	{
		if (pentro1.size() < 5)
		{
			pentro1.push(kobieta);
		}
	}
	if (a == 2)
	{
		if (pentro2.size() < 5)
		{
			pentro2.push(kobieta);
		}
	}
	if (a == 3)
	{
		if (pentro3.size() < 5)
		{
			pentro3.push(kobieta);
		}
	}
	portret(hdc);
}

void windo_jedz(HDC hdc, int &poz_windy, int gora)				//funkcja decydujaca gdzie jedzie winda
{
	if (winda.size() == 8 || poz_windy == 305 && pentro1.size() == 0 || poz_windy == 155 && pentro2.size() == 0 || poz_windy == 5 && pentro3.size() == 0 || (poz_windy != 5 && poz_windy != 155 && poz_windy != 305))
	{
		if (gora == 1)
		{
			poz_windy = poz_windy - 3;
		}
		if (gora == 0)
		{
			poz_windy = poz_windy + 3;
		}
	}
}
int gora = 2;
int blokada = 2;
int u = 0;

void rysowanie_windy(HWND hWnd, HDC hdc, int &poz_windy, int &gora, int &blokada, int &u)			//rysowanie i dzia³anie windy
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 128, 128, 255));
	graphics.DrawRectangle(&pen, 7, poz_windy, 196, 150);		//rysowanie windy
	if (poz_windy == 305)										//winda jest na P1 - wsiadanie/wysiadanie ludzi
	{
		if (winda.size() != 0)
		{
			for (int w = 0; w < winda.size(); w++)
			{
				if (winda.front().konc == 1)
				{
					winda.pop();
				}
				else
				{
					winda.push(winda.front());
					winda.pop();
				}
				gora = 2;
				blokada = 2;
			}
		}
		if (pentro1.size() != 0 & winda.size() < 8)
		{
			for (int k = 0; k < pentro1.size(); k++)
			{
				winda.push(pentro1.front());
				pentro1.pop();
				wybielanie_ludzi(hWnd, hdc, poz_windy);
				portret(hdc);
				gora = 2;
				blokada = 2;
			}
		}
	}
	if (poz_windy == 155)										//winda jest na P2 - wsiadanie/wysiadanie ludzi
	{
		if (winda.size() != 0)
		{
			for (int w = 0; w < winda.size(); w++)
			{
				if (winda.front().konc == 2)
				{
					winda.pop();
				}
				else
				{
					winda.push(winda.front());
					winda.pop();
				}
				gora = 2;
				blokada = 2;
			}
		}
		if (pentro2.size() != 0 & winda.size() < 8)
		{
			for (int k = 0; k < pentro2.size(); k++)
			{
				winda.push(pentro2.front());
				pentro2.pop();
				wybielanie_ludzi(hWnd, hdc, poz_windy);
				portret(hdc);
				gora = 2;
				blokada = 2;
			}
		}
	}
	if (poz_windy == 5)											//winda jest na P3 - wsiadanie/wysiadanie ludzi
	{
		if (winda.size() != 0)
		{
			for (int w = 0; w < winda.size(); w++)
			{
				if (winda.front().konc == 3)
				{
					winda.pop();
				}
				else
				{
					winda.push(winda.front());
					winda.pop();
				}
				gora = 2;
				blokada = 2;
			}
		}
		if (pentro3.size() != 0 & winda.size() < 8)
		{
			for (int k = 0; k < pentro3.size(); k++)
			{
				winda.push(pentro3.front());
				pentro3.pop();
				wybielanie_ludzi(hWnd, hdc, poz_windy);
				gora = 2;
				blokada = 2;
			}
		}
	}

	if ((winda.size() == 0 && (poz_windy == 305 || poz_windy == 155 || poz_windy == 5)) && (pentro1.size() != 0 || pentro2.size() != 0 || pentro3.size() != 0))//zawo³ana winda pos³usznie jedzie
	{
		if (poz_windy == 305 && (pentro2.size() != 0 || pentro3.size() != 0))
		{
			gora = 1;
			blokada = 1;
		}
		if (poz_windy == 5 && (pentro1.size() != 0 || pentro2.size() != 0))
		{
			gora = 0;
			blokada = 0;
		}
		if (poz_windy == 155)
		{
			if (pentro1.size() != 0 && blokada != 1)
			{
				gora = 0;
				blokada = 0;

			}
			if (pentro3.size() != 0 && blokada != 0)
			{
				gora = 1;
				blokada = 1;

			}
		}
	}
	if (winda.size() != 0)									//priorytet piêter
	{
		if (poz_windy == 305 && winda.front().konc != 1)
		{
			gora = 1;
			blokada = 1;
		}
		if (poz_windy == 5 && winda.front().konc != 3)
		{
			gora = 0;
			blokada = 0;
		}
		if (poz_windy == 155 && winda.front().konc == 3)
		{
			gora = 1;
			blokada = 1;
		}
		if (poz_windy == 155 && winda.front().konc == 1)
		{
			gora = 0;
			blokada = 0;
		}
	}
	for (int k = 0; k < winda.size(); k++)						//rysowanie ludzi w windzie
	{
		graphics.DrawRectangle(&pen, 18 + k * 22, poz_windy + 75, 18, 60);
	}
	if (winda.size() == 0 && pentro1.size() == 0 && pentro1.size() == 0 && pentro1.size() == 0 && gora == 2)	//zjazd windy po 5s
	{
		u++;
	}
	if (u > 200)
	{
		gora = 0;
		blokada = 0;
		if (poz_windy == 305)
		{
			gora = 2;
			blokada = 2;
			u = 0;
		}
	}

	windo_jedz(hdc, poz_windy, gora);				//wywo³anie ruchu windy
}




int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 25, 0);
	return 0;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HWND hWnd_przycisk;


	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 50, 50, 600, 600, NULL, NULL, hInstance, NULL);

	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 310, 20, 20, hWnd, (HMENU)ID_P1K2, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 335, 20, 20, hWnd, (HMENU)ID_P1K3, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 160, 20, 20, hWnd, (HMENU)ID_P2K1, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 185, 20, 20, hWnd, (HMENU)ID_P2K3, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 10, 20, 20, hWnd, (HMENU)ID_P3K1, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 35, 20, 20, hWnd, (HMENU)ID_P3K2, hInstance, NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
int poz_windy = 305;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);
	int a, b;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_P1K2:									//przyciski i ich funkcje
		{
			int a = 1;
			int b = 2;
			dzielostworzenia(hWnd, a, b);
			break;
		}
		case ID_P1K3:
		{
			int a = 1;
			int b = 3;
			dzielostworzenia(hWnd, a, b);
			break;
		}
		case ID_P2K1:
		{
			int a = 2;
			int b = 1;
			dzielostworzenia(hWnd, a, b);
			break;
		}
		case ID_P2K3:
		{
			int a = 2;
			int b = 3;
			dzielostworzenia(hWnd, a, b);
			break;
		}
		case ID_P3K1:
		{
			int a = 3;
			int b = 1;
			dzielostworzenia(hWnd, a, b);
			break;
		}
		case ID_P3K2:
		{
			int a = 3;
			int b = 2;
			dzielostworzenia(hWnd, a, b);
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		rysuj_pentro(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			RECT drawArea = { 6, 6, 204, 455 };			//rysowanie windy
			InvalidateRect(hWnd, &drawArea, TRUE);
			hdc = BeginPaint(hWnd, &ps);
			rysowanie_windy(hWnd, hdc, poz_windy, gora, blokada, u);	//obs³uga windy
			EndPaint(hWnd, &ps);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
