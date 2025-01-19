#include <vector>
#include <iostream>
#include <random>

#include <gameField.h>
#include <gameWindowBuffer.h>

#define SNAKE 1
#define FOOD 2
GameField::GameField()
{
    this->direction = MOVING_RIGHT;
    this->head = { 0, 0 };
    this->food = { rand() % 70, rand() % 50 };
    this->grid = new char *[60];
    for (int i = 0; i < 60; i++)
    {
        this->grid[i] = new char[80];
    }
    this->tail = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
}
GameField::~GameField()
{
    for (int i = 0; i < 60; i++)
    {
        delete [] this->grid[i];
    }
    delete [] this->grid;
}
void GameField::GenerateGrid()
{
    
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            if (this->head.x == j && this->head.y == i)
            {
                this->grid[i][j] = SNAKE;
            }
            else if (this->food.x == j && this->food.y == i)
            {
                this->grid[i][j] = FOOD;
            }
            else
            {
                this->grid[i][j] = 0;
            }
            for (int k = 0; k < this->tail.size(); k++)
            {
                if (this->tail[k].x == j && this->tail[k].y == i)
                {
                    this->grid[i][j] = SNAKE;
                }
            }
        }
    }
}
void GameField::RenderGameField(GameWindowBuffer &gameWindowBuffer)
{
    int obj_size = 10;
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            switch (this->grid[i][j])
            {
            case SNAKE:
            {
                for (int ii = i * obj_size; ii < i * obj_size + obj_size; ii++)
                {
                    for (int jj = j * obj_size; jj < j * obj_size + obj_size; jj++)
                    {
                        gameWindowBuffer.DrawPixel(jj, ii, 0, 125, 0);
                    }
                }
                break;
            }
            case FOOD:
            {
                for (int ii = i * obj_size; ii < i * obj_size + obj_size; ii++)
                {
                    for (int jj = j * obj_size; jj < j * obj_size + obj_size; jj++)
                    {
                        gameWindowBuffer.DrawPixel(jj, ii, 255, 0, 0);
                    }
                }
                break;
            }
            }
        }
    }
}

void GameField::MoveSnake()
{
    switch (this->direction)
    {
    case MOVING_UP:
    {
        --this->head.y;
        if (this->head.y < 0)
        {
            this->head.y = 58;
        }
        break;
    }
    case MOVING_RIGHT:
    {
        ++this->head.x;
        if (this->head.x > 78)
        {
            this->head.x = 0;
        }
        break;
    }
    case MOVING_DOWN:
    {
        ++this->head.y;
        if (this->head.y > 58)
        {
            this->head.y = 0;
        }
        break;
    }
    case MOVING_LEFT:
    {
        --this->head.x;
        if (this->head.x < 0)
        {
            this->head.x = 78;
        }
        break;
    }
    }


    if (this->grid[this->head.y][this->head.x] == FOOD)
    {
        this->Grove();
        std::cout << "y";
        this->ChangeFoodPos();
    }
    this->tail[0].x = this->head.x;
    this->tail[0].y = this->head.y;
    for (int i = this->tail.size() - 1; i >= 1; i--)
    {
        this->tail[i].x = this->tail[i - 1].x;
        this->tail[i].y = this->tail[i - 1].y;
    }
    

}
void GameField::ChangeDirection(int direction)
{
    if (direction == VK_UP && this->direction != MOVING_DOWN)
        this->direction = MOVING_UP;
    else if (direction == VK_RIGHT && this->direction != MOVING_LEFT)
        this->direction = MOVING_RIGHT;
    else if (direction == VK_DOWN && this->direction != MOVING_UP)
        this->direction = MOVING_DOWN;
    else if (direction == VK_LEFT && this->direction != MOVING_RIGHT)
        this->direction = MOVING_LEFT;
}

void GameField::Grove()
{
    POINT point = { this->tail[0].x, this->tail[0].y };
    this->tail.push_back(point);
}
void GameField::ChangeFoodPos()
{
    this->food.y = rand() % 50;
    this->food.x = rand() % 70;
}