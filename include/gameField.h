#pragma once
#include <vector>
#include <Windows.h>


#include <gameWindowBuffer.h>
enum
{
    MOVING_UP = 0,
    MOVING_RIGHT,
    MOVING_DOWN,
    MOVING_LEFT
};
class GameField
{
public:
    char **grid;
    POINT head;
    std::vector<POINT> tail;
    POINT food;
    int direction;
    GameField();
    ~GameField();
    void RenderGameField(GameWindowBuffer &gameWindowBuffer);
    void GenerateGrid();
    void MoveSnake();
    void ChangeDirection(int direction);
    void Grove();
    void ChangeFoodPos();
};