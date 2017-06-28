// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include "queue"

#define MAX_LOADSTRING 100
#define TMR_1 1
#define P1P2 12
#define P1P3 13
#define P2P1 21
#define P2P3 23
#define P3P1 31
#define P3P2 32

using namespace std;

HINSTANCE hInst;								
TCHAR szTitle[MAX_LOADSTRING];					
TCHAR szWindowClass[MAX_LOADSTRING];			
INT value;
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int kierunek=0;

struct ludz
{
	int start;
	int cel;
};

queue<ludz> pasazerowie;
queue<ludz> pietro1;
queue<ludz> pietro2;
queue<ludz> pietro3;

void rysuj_pietra(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 128, 128, 255));
	Pen pen1(Color(200, 100, 50, 255));
	Pen pen2(Color(150, 200, 300, 255));
	Pen pen3(Color(100, 50, 200, 255));

	graphics.DrawRectangle(&pen, 5, 5, 200, 450);									
	graphics.DrawRectangle(&pen1, 205, 5, 200, 150);									
	graphics.DrawRectangle(&pen2, 205, 156, 200, 150);
	graphics.DrawRectangle(&pen3, 205, 307, 200, 150);
}




void rysuj_poczekalnie(HDC hdc)											
{
	Graphics graphics(hdc);
	Pen pen1(Color(200, 100, 50, 255));
	Pen pen2(Color(150, 200, 300, 255));
	Pen pen3(Color(100, 50, 200, 255));


	for (int i = 0; i < pietro1.size(); i++)
	{
		ludz temp;
		temp = pietro1.front();
		pietro1.pop();
		pietro1.push(temp);

		if (temp.cel == 2)
		{
			graphics.DrawRectangle(&pen2, 220 + i * 30, 380, 20, 60);
		}
		else
		{
			graphics.DrawRectangle(&pen1, 220 + i * 30, 380, 20, 60);
		}
	}
		
	for (int i = 0; i < pietro2.size(); i++)
	{
		ludz temp;
		temp = pietro2.front();
		pietro2.pop();
		pietro2.push(temp);

		if (temp.cel == 1)
		{
			graphics.DrawRectangle(&pen3, 220 + i * 30, 230, 20, 60);
		}
		else
		{
			graphics.DrawRectangle(&pen1, 220 + i * 30, 230, 20, 60);
		}
	}	

	for (int i = 0; i < pietro3.size(); i++)
	{

		ludz temp;
		temp = pietro3.front();
		pietro3.pop();
		pietro3.push(temp);

		if (temp.cel == 2)
		{
			graphics.DrawRectangle(&pen2, 220 + i * 30, 80, 20, 60);
		}
		else 
		{
			graphics.DrawRectangle(&pen3, 220 + i * 30, 80, 20, 60);
		}
	}
}

void wysiadka(HWND hWnd, HDC hdc, int poz_windy)	
{
	RECT drawArea = { 205, poz_windy, 500, poz_windy + 150 };
	InvalidateRect(hWnd, &drawArea, TRUE);
	rysuj_poczekalnie(hdc);
}


void dodaj_ludzia(HWND hWnd, int a, int b)			
{
	HDC hdc = GetDC(hWnd);
	ludz pasazer;
	pasazer.start = a;
	pasazer.cel = b;

	if (a == 1)
	{	
			pietro1.push(pasazer);
	}
	if (a == 2)
	{
			pietro2.push(pasazer);
	}
	if (a == 3)
	{
			pietro3.push(pasazer);
	}
	rysuj_poczekalnie(hdc);
}

void jedz_winda(HDC hdc, int &pozycja, int kierunek)
{		
	
	if (kierunek == 1)
		{
			pozycja = pozycja - 5;
		}
		else if (kierunek == -1)
		{
			pozycja = pozycja + 5;
		}

}



void akcja(HWND hWnd, HDC hdc, int &poz_windy, int &kierunek)
{

	Graphics graphics(hdc);
	Pen pen(Color(255, 128, 128, 255));
	Pen pen1(Color(200, 100, 50, 255));
	Pen pen2(Color(150, 200, 300, 255));
	Pen pen3(Color(100, 50, 200, 255));
	graphics.DrawRectangle(&pen, 7, poz_windy, 196, 150);

	if (poz_windy == 305)
	{
		if (pasazerowie.size() != 0)
		{
			for (int i = 0; i <8* pasazerowie.size(); i++)
			{
				if (pasazerowie.front().cel == 1)
				{
					pasazerowie.pop();
				}
				else
				{
					ludz temp;
					temp = pasazerowie.front();
					pasazerowie.push(temp);
					pasazerowie.pop();
				}
				kierunek = 0;
			}
		}



		for (int i = 0; i < 8*pietro1.size(); i++)
		{
			if (pasazerowie.size() < 8)
			{
				ludz temp = pietro1.front();
				pasazerowie.push(temp);
				pietro1.pop();
				wysiadka(hWnd, hdc, poz_windy);
				kierunek = 0;
			}
		}
	}



	else if (poz_windy == 155)
	{	
		if (pasazerowie.size() != 0)
		{
			for (int i = 0; i <8* pasazerowie.size(); i++)
			{
				if (pasazerowie.front().cel == 2)
				{
					pasazerowie.pop();
				}
				else
				{
					pasazerowie.push(pasazerowie.front());
					pasazerowie.pop();

				}
				kierunek = 0;
			}
		}



			for (int i = 0; i < 8*pietro2.size(); i++)
			{
				if (pasazerowie.size() < 8)
				{
					ludz temp = pietro2.front();
					pasazerowie.push(temp);
					pietro2.pop();
					wysiadka(hWnd, hdc, poz_windy);
					kierunek = 0;
				}
			}
	}


	else if (poz_windy == 5)
	{
		if (pasazerowie.size() != 0)
		{
			for (int i = 0; i < 8 * pasazerowie.size(); i++)
			{
				if (pasazerowie.front().cel == 3)
				{
					pasazerowie.pop();
				}
				else
				{
					ludz temp;
					temp = pasazerowie.front();
					pasazerowie.push(temp);
					pasazerowie.pop();
				}
				kierunek = 0;
			}
		}

			for (int i = 0; i < 8*pietro3.size(); i++)
			{
				if (pasazerowie.size() < 8)
				{
					ludz temp = pietro3.front();
					pasazerowie.push(temp);
					pietro3.pop();
					wysiadka(hWnd, hdc, poz_windy);
					kierunek = 0;
				}
			}
	}


	
	if (poz_windy == 305)
	{
		if (pasazerowie.size() == 8)
		{
			kierunek = 1;
		}
		else if (pietro1.size() == 0 && pasazerowie.size() != 0)
		{
			kierunek = 1;
		}
		else if (pietro2.size()!=0 || pietro3.size() !=0)
		{
			kierunek = 1;
		}
		else
		{
			kierunek = 0;
		}
	}

	else if (poz_windy == 155)
	{
		if (pasazerowie.size() == 8)
		{
			if (pasazerowie.front().cel == 1)
			{
				kierunek = -1;
			}
			else if (pasazerowie.front().cel == 3)
			{
				kierunek = 1;
			}
		}
		else if (pietro2.size() == 0)
		{

		if (pietro1.size() != 0)
		{
			kierunek = -1;
		}
		else if (pietro3.size() != 0)
		{
			kierunek = 1;
		}
		else if (pasazerowie.size() == 0)
		{
			kierunek = 0;
		}
		else if (pasazerowie.front().cel == 1)
				{
					kierunek = -1;
				}
				else if (pasazerowie.front().cel == 3)
				{
					kierunek = 1;
				}
				
			}

	}




		else if (poz_windy == 5)
		{
			if (pasazerowie.size() == 8)
			{
				kierunek = -1;
			}
			else if (pietro3.size() == 0 && pasazerowie.size() !=0)
			{
				kierunek = -1;
			}
			else if (pietro2.size() != 0 || pietro1.size() != 0)
			{
				kierunek = -1;
			}
			else
			{
				kierunek = 0;
			}
		}



	for (int i = 0; i < pasazerowie.size(); i++)
	{
		ludz temp;
		temp = pasazerowie.front();

		if (temp.cel == 1)
		{
			graphics.DrawRectangle(&pen3, 13+ i * 15, poz_windy + 75, 10, 60);
		}
		else if (temp.cel == 2)
		{
			graphics.DrawRectangle(&pen2, 13 + i * 15, poz_windy + 75, 10, 60);
		}
		else if (temp.cel == 3)
		{
			graphics.DrawRectangle(&pen1, 13 + i * 15, poz_windy + 75, 10, 60);
		}

		pasazerowie.push(temp);
		pasazerowie.pop();
		
	}



	jedz_winda(hdc, poz_windy, kierunek);

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

	MSG msg;
	HACCEL hAccelTable;

	value = 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HWND hWnd_przycisk;


	hInst = hInstance; 

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 50, 50, 600, 600, NULL, NULL, hInstance, NULL);

	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 310, 20, 20, hWnd, (HMENU) P1P2, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 335, 20, 20, hWnd, (HMENU) P1P3, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 160, 20, 20, hWnd, (HMENU) P2P1, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 185, 20, 20, hWnd, (HMENU) P2P3, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 10, 20, 20, hWnd, (HMENU) P3P1, hInstance, NULL);
	hWnd_przycisk = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 380, 35, 20, 20, hWnd, (HMENU) P3P2, hInstance, NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


int poz_windy = 305;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


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
		case P1P2:									
		{
			dodaj_ludzia(hWnd, 1, 2);
			break;
		}
		case P1P3:
		{
			dodaj_ludzia(hWnd, 1, 3);
			break;
		}
		case P2P1:
		{
			dodaj_ludzia(hWnd, 2, 1);
			break;
		}
		case P2P3:
		{
			dodaj_ludzia(hWnd, 2, 3);
			break;
		}
		case P3P1:
		{
			dodaj_ludzia(hWnd, 3, 1);
			break;
		}
		case P3P2:
		{
			dodaj_ludzia(hWnd, 3, 2);
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		rysuj_pietra(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			RECT drawArea = { 6, 6, 204, 455 };			
			InvalidateRect(hWnd, &drawArea, TRUE);
			hdc = BeginPaint(hWnd, &ps);	
			akcja(hWnd, hdc, poz_windy, kierunek);	
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
