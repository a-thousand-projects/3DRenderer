#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "triangle.h"
#include "display.h"
#include "swap.h"

void fill_flatBottomTriangle(int x0,int y0,int x1,int y1,int x2,int y2, uint32_t color);

void fill_flatToppedTriangel(int x0,int y0,int x1,int y1,int x2,int y2, uint32_t color);



void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color)
{
    drawLine(x, y, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x, y, color);
}




///////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
//
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
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


/**************************************************************************/
/*                 TEXTURED FUNCTIONS                                     */
/**************************************************************************/


///////////////////////////////////////////////////////////////////////////////
// Return the barycentric weights alpha, beta, and gamma for point p
///////////////////////////////////////////////////////////////////////////////
//
//         (B)
//         /|\
//        / | \
//       /  |  \
//      /  (P)  \
//     /  /   \  \
//    / /       \ \
//   //           \\
//  (A)------------(C)
//
///////////////////////////////////////////////////////////////////////////////
vct3_t barycentric_weights(vct2_t a, vct2_t b, vct2_t c, vct2_t p)
{
    // find the vectors between the vertices ABC and point p
    vct2_t ac = vct2Subtract(c, a);
    vct2_t ab = vct2Subtract(a, a);
    vct2_t ap = vct2Subtract(p, a);
    vct2_t pc = vct2Subtract(c, p);
    vct2_t pb = vct2Subtract(b, p);

    // Calculate the area of the full parallelogram ABC using 2d cross product
    float areaParallelogramABC = (ac.x * ab.y - ac.y * ab.x);

    // Alpha is the area of the small parallelogram triangle PBC devided by the full parallelogram area
    float alpha = (pc.x * pb.y - pc.y * pb.x) / areaParallelogramABC;

    // Beta is the area of the small parallelogram triangle APC devided by the full parallelogram area
    float beta = (ac.x * ap.y - ac.y * ap.x) / areaParallelogramABC;

    // Gamma is the remainder of the other two minus 1
    float gamma = 1 - alpha - beta;

    vct3_t weights = { alpha,beta,gamma };
    return weights;
}



/*
* Draw texture pixel
*/
void drawTexel(int x, int y, vct2_t pointA, vct2_t pointB, vct2_t pointC,
    float u0, float v0, float u1, float v1, float u2, float v2, uint32_t* texture)
{
    vct2_t pointP = { x,y };
    vct3_t weights = barycentric_weights(pointA, pointB, pointC, pointP);
    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;

    float interpolatedU = u0 * alpha + u1*beta + u2 * gamma;
    float interpolatedV = v0 * alpha + v1 * beta + v2 * gamma;

    int texX = abs(interpolatedU * textureWidth);
    int texY = abs(interpolatedV * textureHeight);


    // todo : check for buffer overflow in texture array
    int texPos = (textureWidth * texY) + texX;
    if (texPos < sizeof(texture)) {
        drawPixel(x, y, texture[(textureWidth * texY) + texX]);
    }
}


///////////////////////////////////////////////////////////////////////////////
// Draw a textured triangle based on a texture array of colors.
// We split the original triangle in two, half flat-bottom and half flat-top.
///////////////////////////////////////////////////////////////////////////////
//
//        v0
//        /\
//       /  \
//      /    \
//     /      \
//   v1--------\
//     \_       \
//        \_     \
//           \_   \
//              \_ \
//                 \\
//                   \
//                    v2
//
///////////////////////////////////////////////////////////////////////////////
void drawTexturedTriangle(
    int x0, int y0, float u0, float v0,
    int x1, int y1, float u1, float v1,
    int x2, int y2, float u2, float v2,
    uint32_t* texture)
{
    // Sort by y value (y < y1 < y2)
    // Sort vertices by Y coordinates y1 < Y2 < y3
    if (y0 > y1)
    {
        intSwap(&y0, &y1);
        intSwap(&x0, &x1);
        floatSwap(&u0, &u1);
        floatSwap(&v0, &v1);
    }
    if (y1 > y2)
    {
        intSwap(&y1, &y2);
        intSwap(&x1, &x2);
        floatSwap(&u1, &u2);
        floatSwap(&v1, &v2);
    }
    if (y0 > y1)
    {
        intSwap(&y0, &y1);
        intSwap(&x0, &x1);
        floatSwap(&u0, &u1);
        floatSwap(&v0, &v1);
    }

    // Set up pixel vectors
    vct2_t pointA = { x0, y0 };
    vct2_t pointB = { x1, y1 };
    vct2_t pointC = { x2, y2 };

    /////////////////////////////////////////////
    // Render Upper part of triangle
    /////////////////////////////////////////////
    float invSlope1 = 0;
    float invSlope2 = 0;

    if (y1 - y0 != 0) 
        invSlope1 = (float)(x1 - x0) / abs(y1 - y0);
    if (y2 - y0 != 0) 
        invSlope2 = (float)(x2 - x0) / abs(y2 - y0);
    if (y1 - y0 != 0)
    {
        for (int y = y0; y < y1; y++)
        {
            int xStart = x1 + (y - y1) * invSlope1;
            int xEnd = x0 + (y - y0) * invSlope2;
            uint32_t col = 0xCD127700;
            if (xStart > xEnd)
            {
                intSwap(&xStart, &xEnd);
            }
            for (int x = xStart; x < xEnd; x++)
            {
                //drawPixel(x, y, (x%2 == 0 && y%2 == 00) ?0xFF1277FF: 0xFF000000);
                drawTexel(x, y, pointA,pointB,pointC,u0,v0,u1,v1,u2,v2, texture);
            }

        }
    }

    /////////////////////////////////////////////
    // Render Lower part of triangle
    /////////////////////////////////////////////

    if (y2- y1 != 0)
        invSlope1 = (float)(x2 - x1) / abs(y2 - y1);
    if (y2 - y0 != 0)
        invSlope2 = (float)(x2 - x0) / abs(y2 - y0);

    if (y2 - y0 != 0)
    {
        for (int y = y1; y < y2; y++)
        {
            int xStart = x1 + (y - y1) * invSlope1;
            int xEnd = x0 + (y - y0) * invSlope2;
            
            if (xStart > xEnd)
            {
                intSwap(&xStart, &xEnd);
            }
            for (int x = xStart; x < xEnd; x++)
            {
                //drawPixel(x, y, 0xFF00AA33);
                drawTexel(x, y, pointA, pointB, pointC, u0, v0, u1, v1, u2, v2, texture);
            }

        }
    }

}