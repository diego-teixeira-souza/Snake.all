#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define true 1
#define false 0
#define max_speed 3

typedef int bool;

bool isGameOver, isRuning;
int snake_x, snake_y, food_x, food_y, tail_length, tail_x[100], tail_y[100], width, height, score, speed;
char direction;

bool isTail(const int x, const int y)
{
     for(int t = 0; t < tail_length; t ++)
        if (x == tail_x[t] && y == tail_y[t])
            return true;
    return false;
}
void food()
{
    time_t tm;
    srand((unsigned) &tm);
    while(true)
    {
        int x = rand() % width;
        int y = rand() % height;
        if (!(y == snake_y && x == snake_x) || (y == 1 || y == height || x == 1 || x == width) && !isTail(x, y))
        {
            food_x = x;
            food_y = y;
            break;
        }
    }
}
void render()
{
    system("cls");
    for(int y = 1; y <= height; y++)
    {
        printf("\n");
        for(int x = 1; x <= width; x++)
        {
            if (y == 1 || y == height || x == 1 || x == width)
                printf("+");
            else if (y == food_y && x == food_x)
                printf("F");
            else if (y == snake_y && x == snake_x)
                printf("O");
            else if (isTail(x, y))
                printf("o");
            else
                printf(" ");
        }
    }

    if (isGameOver == true)
    {
        printf("\nYou score : %d. Press x to exit", score);
        char key;
        while(key != 'x')
            key = _getch();
    }
}
void setup()
{
    isGameOver = false;
    width = 100;
    height = 30;
    snake_x = width / 2;
    snake_y = height / 2;
    tail_length = 0;
    direction = 'w';
    score = 0;
    speed = 1;
    food();
    render();
}
void logic()
{   
    if (_kbhit())
	{
        char keyPressed = _getch();
        if ((keyPressed == 'w' && direction != 's') || (keyPressed == 'a' &&  direction != 'd')
        || (keyPressed == 's' && direction != 'w') || (keyPressed == 'd' && direction != 'a')){
            if (keyPressed == direction){
                speed += 1;
                if (speed > max_speed)
                    speed = max_speed;
            }
            direction = keyPressed;
        }
	}else
        speed = 1;

    bool isFood = false;
    for (int i = 0; i < speed; i++)
    {
        int prevX = snake_x;
        int prevY = snake_y;
        switch(direction)
        {
            case 'w':
                snake_y -= 1;
                break;
            case 'a':
                snake_x -= 1;
                break;
            case 's':
                snake_y += 1;
                break;
            case 'd':
                snake_x += 1;
                break;
        }
        
        if (snake_x == food_x && snake_y == food_y){
            tail_length += 1;
            score += 1;
            isFood = true;
        } else if (snake_y == 1 || snake_y == height || snake_x == 1 || snake_x == width || isTail(snake_x, snake_y))
            isGameOver = true;

        int prev_tail_x;
        int prev_tail_y;
        for(int t = 0; t < tail_length; t++)
        {
            prev_tail_x = tail_x[t];
            prev_tail_y = tail_y[t];
            tail_x[t] = prevX;
            tail_y[t] = prevY;
            prevX = prev_tail_x;
            prevY = prev_tail_y;
        }
    }

    if (isFood == true)
        food();
}
void sync()
{
    Sleep(60);
}
void run()
{
    setup();
    while(isGameOver == false)
    {
        logic();
        render();
        sync();
    }
}

int main(int argc, char * argv[])
{
    run();
    return 0;
}