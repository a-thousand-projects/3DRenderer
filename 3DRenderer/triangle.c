#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "triangle.h"
#include "display.h"

void intSwap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void drawFilledTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color)
{
    // Sort vertices by Y coordinates y1 < Y2 < y3
    if (y > y1)
    {
        intSwap(&y, &y1);
        intSwap(&x, &x1);
    }
    if (y1 > y2)
    {
        intSwap(&y1, &y2);
        intSwap(&x1, &x2);
    }
    if (y > y1)
    {
        intSwap(&y, &y1);
        intSwap(&x, &x1);
    }

    // Calc (Mx,My) using similar triangles
    int my = y1;
    int mx = ((float)((x2 - x)*(y1 = y)) / (float)(y2 - y)) + x;

    // Draw flat bottomed triange
    // Draw flat Topped triangle

    fill_flatBottomTriangle(x,y,x1,y1,mx,my);

    fill_flatToppedTriangel(x1,y1,mx,my,x2,y2);
}