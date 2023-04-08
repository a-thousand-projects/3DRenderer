#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "triangle.h"
#include "display.h"

void fill_flatBottomTriangle(int x,int y,int x1,int y1,int mx,int my, uint32_t color);

void fill_flatToppedTriangel(int x1,int y1,int mx,int my,int x2,int y2, uint32_t color);

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
    int mx = ((float)((x2 - x)*(y1 - y)) / (float)(y2 - y)) + x;

    // Draw flat bottomed triange
    // Draw flat Topped triangle

    fill_flatBottomTriangle(x,y,x1,y1,mx,my, color);

    fill_flatToppedTriangel(x1,y1,mx,my,x2,y2,color);
}

void fill_flatBottomTriangle(int x0, int y0, int x1, int y1, int mx, int my,uint32_t color)
{
    float invSlope1 = (float)(x1 - x0) / (float)(y1 - y0);
    float invSlope2 = (float)(mx - x0) / (float)(my - y0);
    float xStart = x0;
    float xEnd = x0;
    for (int y = y0; y <= y1; y++)
    {
        drawLine(xStart, y, xEnd , y, color);
        xStart += invSlope1;
        xEnd += invSlope2;
        
    }
 }

void fill_flatToppedTriangel(int x1, int y1, int mx, int my, int x2, int y2, uint32_t color)
{

}
