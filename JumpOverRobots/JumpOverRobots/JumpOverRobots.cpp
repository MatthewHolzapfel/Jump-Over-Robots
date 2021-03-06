﻿// JumpOverRobots.cpp : Defines the entry point for the application.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "stdafx.h"
#include "JumpOverRobots.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "HardwareCheck.h"
#include "InputDebug.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#include "Physics.h"
#include "AI.h"
#include <assert.h>

//#include <conio.h>

using namespace std; 

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK    WindowsProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)

{
	//Placeholder - initializing physics, AI here

	//Testing SFML
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	////////////////////////////////////////////SFML SOUND
/*	sf::Event event;
	sf::Music music;
	//if (!music.openFromFile("MarioBGM.ogg"))
	music.openFromFile("Jump-Over-Robots-master/JumpOverRobots/MarioBGM.ogg");
		//return EXIT_FAILURE;
		music.setVolume(50);
	music.play(); */

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	//Testing SFML
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	string startBuild = "";
	if (singleInstance)
		startBuild = "Just one!\n";
	else
		startBuild = "Multiple?\n";	
	OutputDebugStringA(startBuild.c_str());
	
	if (storage())
		startBuild = "You've got enough space!\n";
	else
		startBuild = "Not enough space!\n";
	OutputDebugStringA(startBuild.c_str());

	memTest();
	ArchitectureInfo();
	speed();

    // TODO: Place code here.

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	printf_s("Hello");

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "test.lua");
	lua_close(L);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JUMPOVERROBOTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JUMPOVERROBOTS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    return (int) msg.wParam;
}




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JUMPOVERROBOTS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JUMPOVERROBOTS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
/*LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t msg[32];
    switch (message)
    {

	case WM_LBUTTONDOWN:
	{
		int iPosX = LOWORD(lParam);
		int iPosY = HIWORD(lParam);
		wchar_t waCoord[20];
		wsprintf(msg, _T("LM Down (%i, %i)\n"), iPosX, iPosY);
		OutputDebugString(msg);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		int iPosX = LOWORD(lParam);
		int iPosY = HIWORD(lParam);
		wchar_t waCoord[20];
		wsprintf(msg, _T("RM Down (%i, %i)\n"), iPosX, iPosY);
		OutputDebugString(msg);
		break;
	}
	case WM_LBUTTONUP:
	{
		int iPosX = LOWORD(lParam);
		int iPosY = HIWORD(lParam);
		wchar_t waCoord[20];
		wsprintf(msg, _T("LM Up (%i, %i)\n"), iPosX, iPosY);
		OutputDebugString(msg);
		break;
	}
	case WM_RBUTTONUP:
	{
		int iPosX = LOWORD(lParam);
		int iPosY = HIWORD(lParam);
		wchar_t waCoord[20];
		wsprintf(msg, _T("RM Up (%i, %i)\n"), iPosX, iPosY);
		OutputDebugString(msg);
		break;
	}
	case WM_SYSKEYDOWN:
	{
		swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;
	}
	case WM_SYSCHAR:
	{
		swprintf_s(msg, L"WM_SYSCHAR: %s\n", (wchar_t)wParam);
		OutputDebugString(msg);
		break;
	}
	case WM_SYSKEYUP:
	{
		swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;
	}
	case WM_KEYDOWN:
	{
		swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;
	}
	case WM_KEYUP:
	{
		swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;
	}
	case WM_CHAR:
	{
		swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
		OutputDebugString(msg);
		break;
	}
	/*	switch (wParam)
		{
		case VK_LEFT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Left Arrow Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_RIGHT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Right Arrow Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_UP:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Up Arrow Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}
		case VK_DOWN:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Down Arrow Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_HOME:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Home Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_END:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"End Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_INSERT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Insert Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_DELETE:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Delete Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F1:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F1 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F2:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F2 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F3:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F3 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F4:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F4 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F5:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F5 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F6:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F6 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F7:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F7 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F8:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F8 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F9:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F9 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F10:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F10 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F11:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F11 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_F12:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F12 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_SHIFT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Shift Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_BACK:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Backspace Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_TAB:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Tab Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_CLEAR:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Clear Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_RETURN:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Enter Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_CONTROL:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Control Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_MENU:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Alt Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		} 

		case VK_PAUSE:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Pause Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_CAPITAL:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Caps Lock Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_ESCAPE:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Escape Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_SPACE:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Space Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_PRINT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Print Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case VK_SNAPSHOT:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Snapshot Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x30:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"0 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x31:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"1 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x32:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"2 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x33:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"3 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}
		
		case 0x34:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"4 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x35:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"5 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x36:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"6 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x37:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"7 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x38:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"8 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x39:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"9 Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x41:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"A Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x42:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"B Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x43:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"C Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x44:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"D Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x45:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"E Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x46:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"F Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x47:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"G Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x48:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"H Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x49:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"I Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4A:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"J Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4B:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"K Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4C:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"L Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4D:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"M Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4E:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"N Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x4F:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"O Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x50:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"P Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		} 
		case 0x51:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Q Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x52:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"R Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x53:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"S Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		} 

		case 0x54:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"T Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x55:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"U Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x56:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"V Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x57:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"W Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x58:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"X Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}
		
		case 0x59:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Y Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		case 0x5A:
		{
			wchar_t waCoord[20];
			wsprintf(waCoord, L"Z Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}

		default:

			wchar_t waCoord[20];
			wsprintf(waCoord, L"Any Key");
			::MessageBox(hWnd, waCoord, L"Keyboard", MB_OK);
			break;
		}





    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}*/

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



/*LRESULT CALLBACK WindowsProc(WPARAM wParam)
{
	switch (wParam)
		case WM_KEYDOWN:
	{
		wchar_t waCoord[20];
		wsprintf(waCoord, L"Key");
		::MessageBox(hWnd, waCoord,NULL,MB_OK);
	//case WM_KEYDOWN:
	case VK_LEFT:

		// Process the LEFT ARROW key. 

		break;

	case VK_RIGHT:

		// Process the RIGHT ARROW key. 

		break;

	case VK_UP:

		// Process the UP ARROW key. 

		break;

	case VK_DOWN:

		// Process the DOWN ARROW key. 

		break;

	case VK_HOME:

		// Process the HOME key. 

		break;

	case VK_END:

		// Process the END key. 

		break;

	case VK_INSERT:

		// Process the INS key. 

		break;

	case VK_DELETE:

		// Process the DEL key. 

		break;

	case VK_F2:

		// Process the F2 key. 

		break;


		// Process other non-character keystrokes. 

	default:
		return NULL;
		break;
	}
} 

/*int _tmain(int argc, _TCHAR* argv[])
{
	int number1, number2, product, sum; 

	cout << "Please enter an integer (whole number) \n";
	cin >> number1; 
	cout << "Please enter another integer (whole number) \n"; 
	cin >> number2; 

	product = number1 * number2;
	sum = number1 + number2;

	cout << "The sum of " << number1 << " and " << number2 << " is " << sum << "\n";
	cout << "The product of " << number1 << " and " << number2 << " is " << product << "\n";
	_getch();
	return 0;
}*/

///////////SCENE GRAPH
/*
class SceneNode
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
};


void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
};

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) -> bool {
		return p.get() == &node;
	});

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::RenderWindow window(); 
	SceneNode::Ptr node(); 
	

//	sf::Transformable::getTransform(); 
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (auto itr = mChildren.begin();
		itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target, states);
	}

	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}

	

	
} 

class Sprite : public Entity
{
public: 
	explicit Sprite(Type type);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 

private:
	Type mType;
	sf::Sprite mSprite; 
};

void Sprite::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states); 
} */


