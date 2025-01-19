#include <Windows.h>
#include <iostream>

#include <gameWindowBuffer.h>

void GameWindowBuffer::CreateWindowBuffer(HWND hwnd, BITMAPINFO* bitmapInfo)
{
	RECT rect = { };
	GetClientRect(hwnd, &rect);
	this->w = rect.right;
	this->h = rect.bottom;
	if (this->memory)
	{
		delete[] this->memory;
	}
	this->memory = new unsigned char[4 * this->w * this->h];
	bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
	bitmapInfo->bmiHeader.biWidth = this->w;
	bitmapInfo->bmiHeader.biHeight = -this->h;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biBitCount = 32;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
}

void GameWindowBuffer::ClearWindow()
{
	for (int i = 0; i < this->h; i++)
	{
		for (int j = 0; j < this->w; j++)
		{
			this->memory[4 * (i * this->w + j) + 0] = 0;
			this->memory[4 * (i * this->w + j) + 1] = 0;
			this->memory[4 * (i * this->w + j) + 2] = 0;
			this->memory[4 * (i * this->w + j) + 3] = 0;
		}
	}
}

bool GameWindowBuffer::DrawPixel(int x, int y, BYTE r, BYTE g, BYTE b)
{
	if (x >= this->w || x < 0 || y >= this->h || y < 0)
	{
		return 0;
	}
	this->memory[4 * (y * this->w + x) + 0] = b;
	this->memory[4 * (y * this->w + x) + 1] = g;
	this->memory[4 * (y * this->w + x) + 2] = r;
	this->memory[4 * (y * this->w + x) + 3] = 0;
	return 1;
}