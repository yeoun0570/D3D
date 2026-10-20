#pragma once

#include <windows.h>

using namespace std;

namespace Client
{
	// constexpr : 컴파일 타임에 실행하도록 지시하는 키워드
	static constexpr unsigned int		g_iWinSizeX = { 1280 };
	static constexpr unsigned int		g_iWinSizeY = { 720 };
}

extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;