#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "triangle.h"
#include "display.h"

void fill_flatBottomTriangle(int x0,int y0,int x1,int y1,int x2,int y2, uint32_t color);

void fill_flatToppedTriangel(int x0,int y0,int x1,int y1,int x2,int y2, uint32_t color);

void intSwap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    // Sort vertices by Y coordinates y1 < Y2 < y3
    if (y0 > y1)
    {
        intSwap(&y0, &y1);
        intSwap(&x0, &x1);
    }
    if (y1 > y2)
    {
        intSwap(&y1, &y2);
        intSwap(&x1, &x2);
    }
    if (y0 > y1)
    {
        intSwap(&y0, &y1);
        intSwap(&x0, &x1);
    }

    if (y1 == y2)
    {
        fill_flatBottomTriangle(x0, y0, x1, y1, x2, y2,color);
        return;
    }

    if (y1 == y0)
    {
        fill_flatToppedTriangel(x0, y0, x1, y1, x2, y2, color);
        return;
    }



    // Calc (Mx,My) using similar triangles
    int my = y1;
    int mx = ((float)((x2 - x0)*(y1 - y0)) / (float)(y2 - y0)) + x0;

    // Draw flat bottomed triange
    

    fill_flatBottomTriangle(x0,y0,x1,y1,mx,my, color);
    
    // Draw flat Topped triangle
    fill_flatToppedTriangel(x1,y1,mx,my,x2,y2,color);
}



void fill_flatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2,uint32_t color)
{
    float invSlope1 = (float)(x1 - x0) / (y1 - y0);
    float invSlope2 = (float)(x2 - x0) / (y2 - y0);
    float xStart = x0;
    float xEnd = x0;
    for (int y = y0; y <= y2; y++)
    {
        drawLine(xStart, y,xEnd,y, color);

        xStart += invSlope1;
        xEnd += invSlope2;
        
    }
 }

void fill_flatToppedTriangel(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    float invSlope1 = (float)(x2 - x0) / (y2 - y0);
    float invSlope2 = (float)(x2 - x1) / (y2 - y1);
    float xStart = x2;
    float xEnd = x2;
    for (int y = y2; y >= y0; y--)
    {
        //drawHorzLine(xStart, y, (mx-x1), color);
        drawLine(xStart, y, xEnd, y, color);
        xStart -= invSlope1;
        xEnd -= invSlope2;
    }
}
