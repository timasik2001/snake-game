#pragma once
#include <iostream>
#include <Windows.h>

class GameWindowBuffer
{
public:
	int w = 800;
	int h = 600;
	unsigned char* memory = nullptr;
	void CreateWindowBuffer(HWND hwnd, BITMAPINFO* bitmapInfo);
	void ClearWindow();
	bool DrawPixel(int x, int y, BYTE r, BYTE g, BYTE b);
	
};