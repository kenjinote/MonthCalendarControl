#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "comctl32")

#include <windows.h>
#include <commctrl.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hMonthCAL;
	static HWND hEdit;
	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();
		hMonthCAL = CreateWindow(MONTHCAL_CLASS, 0, WS_VISIBLE | WS_CHILD | MCS_DAYSTATE, 0, 0, 256, 256, hWnd, (HMENU)100, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hEdit = CreateWindow(TEXT("EDIT"), 0, WS_CHILD | WS_VISIBLE | ES_CENTER | ES_READONLY, 0, 256, 256, 256, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_NOTIFY:
		{
			LPNMHDR lpNMHDR = (LPNMHDR)lParam;
			if (lpNMHDR->idFrom != 100)
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			LPNMSELCHANGE lpSChange = (LPNMSELCHANGE)lParam;
			switch (lpSChange->nmhdr.code)
			{
			case MCN_SELCHANGE:
			{
				SYSTEMTIME st;
				MonthCal_GetCurSel(hMonthCAL, &st);
				TCHAR szText[1024];
				wsprintf(szText, TEXT("%04d/%02d/%02d"), st.wYear, st.wMonth, st.wDay);
				SetWindowText(hEdit, szText);
			}
			break;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("カレンダーコントロールのサンプル"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}