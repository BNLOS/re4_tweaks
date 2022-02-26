#include <iostream>
#include "stdafx.h"
#include "dllmain.h"
#include "cfgMenu.h"
#include "WndProcHook.h"
#include "Settings.h"
#include "ConsoleWnd.h"
#include "input.hpp"
#include "Logging/Logging.h"

WNDPROC oWndProc;
HWND hWindow;

int curPosX;
int curPosY;

// Our new hooked WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_MOVE:
			// Get current window position
			curPosX = (int)(short)LOWORD(lParam);   // horizontal position 
			curPosY = (int)(short)HIWORD(lParam);   // vertical position 
			break;

		case WM_EXITSIZEMOVE:
			if (cfg.bRememberWindowPos)
			{
				// Write new window position
				#ifdef VERBOSE
				con.AddConcatLog("curPosX = ", curPosY);
				con.AddConcatLog("curPosY = ", curPosX);
				#endif

				CIniReader iniReader("");

				cfg.iWindowPositionX = curPosX;
				cfg.iWindowPositionY = curPosY;

				iniReader.WriteInteger("DISPLAY", "WindowPositionX", curPosX);
				iniReader.WriteInteger("DISPLAY", "WindowPositionY", curPosY);
			}
			break;

		case WM_CLOSE:
			ExitProcess(0);
			break;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

// CreateWindowExA hook to get the hWindow and set up the WndProc hook
HWND __stdcall CreateWindowExA_Hook(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	int windowX = cfg.iWindowPositionX < 0 ? CW_USEDEFAULT : cfg.iWindowPositionX;
	int windowY = cfg.iWindowPositionY < 0 ? CW_USEDEFAULT : cfg.iWindowPositionY;

	HWND result = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, cfg.bWindowBorderless ? WS_POPUP : dwStyle, windowX, windowY, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	hWindow = result;

	Logging::Log() << __FUNCTION__ << " -> Window created. Registering for input...";

	// Register hWnd for input processing
	_input = input::register_window(hWindow);

	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);

	return result;
}

void Init_WndProcHook()
{
	// CreateWindowEx hook
	auto pattern = hook::pattern("68 00 00 00 80 56 68 ? ? ? ? 68 ? ? ? ? 6A 00");
	injector::MakeNOP(pattern.get_first(0x12), 6);
	injector::MakeCALL(pattern.get_first(0x12), CreateWindowExA_Hook, true);
}