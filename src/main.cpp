#include <iostream>
#include <windows.h>
#include <chrono>


#include <gameWindowBuffer.h>
#include <gameField.h>
class WindowStuff
{
public:
    bool running = true;
    BITMAPINFO bitmapInfo = { };
    GameWindowBuffer gameWindowBuffer = { };
};

WindowStuff windowStuff;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_CLOSE:
    {
        windowStuff.running = false;
        break;
    }
    case WM_SIZE:
    {
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC DeviceContext = BeginPaint(hwnd, &ps);
        HDC hdc = GetDC(hwnd);
        // filling the window with our gamewindowbuffer array
        StretchDIBits(hdc,
            0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
            0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
            windowStuff.gameWindowBuffer.memory,
            &windowStuff.bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY
        );

        ReleaseDC(hwnd, hdc);

        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int main()
{

#pragma region creating window
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "Sample Window Class";
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "Snake game", 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, 
        NULL,
        wc.hInstance,  
        NULL        
    );

    if (hwnd == NULL)
    {
        return 0;
    }

#pragma endregion


    windowStuff.gameWindowBuffer.CreateWindowBuffer(hwnd, &windowStuff.bitmapInfo);
    MSG msg = { };
    GameField gameField;
    int iter = 0;
    while (windowStuff.running)
    {
        ++iter;
        if (iter > gameField.frec)
        {
            iter = 0;
            gameField.MoveSnake();
            
        }
        windowStuff.gameWindowBuffer.ClearWindow();
        gameField.GenerateGrid();
        gameField.RenderGameField(windowStuff.gameWindowBuffer);
        SendMessage(hwnd, WM_PAINT, 0, 0);
        std::cout << gameField.head.x << ' ' << gameField.head.y << std::endl;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            gameField.ChangeDirection(msg.wParam);
        }
        
    }
    return 0;
}