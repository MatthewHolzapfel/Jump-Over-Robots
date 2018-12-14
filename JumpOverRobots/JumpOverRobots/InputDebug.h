#pragma once
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			//case IDM_ABOUT:
			//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			//	break;
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
}
