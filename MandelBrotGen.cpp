#include "MandelBrotGen.h"
#include "MandelBrotThread.h"
#include "MandelBrotCommon.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/** @brief ChkMandelBrotSet
  *
  * @todo: document this function
  */
bool MandelBrotGen::ChkMandelBrotSet(double a, double b, int * reqIncrement)
{
    return false;
}

/** @brief MandelBrotGen
  *
  * @todo: document this function
  */
 MandelBrotGen::MandelBrotGen(int x_Res, int y_Res, SDL_Surface * screen)
{
    numBlksThreads = MB_THREADS_NUM;
    this->xRes = x_Res;
    this->yRes = y_Res;
    drawScreen = screen;

    if(MB_THREADS_NUM % 2)
    {
        numBlksThreads = MB_THREADS_NUM + 1;
    }

    xDiv = 2;
    yDiv = numBlksThreads / xDiv;

    a_increment = (A_END - A_BEGIN)/(double)xRes;
    b_increment = (B_END - B_BEGIN)/(double)yRes;

    printf("\r\n Creating threads for Mandel Brot : %d", numBlksThreads);
}

/** @brief StartGeneratingMB
  *
  * @todo: document this function
  */
void MandelBrotGen::StartGeneratingMB()
{
    CreateMBThreads();
}

/** @brief StartGeneratingMB
  *
  * @todo: document this function
  */
void MandelBrotGen::StartGeneratingMB(int xBegin, int yBegin, int xEnd, int yEnd)
{

}

/** @brief MandelBrotGen
  *
  * @todo: document this function
  */
 MandelBrotGen::MandelBrotGen()
{

}

/** @brief CreateMBThreads
  *
  * @todo: document this function
  */
int MandelBrotGen::CreateMBThreads()
{
    int thrd_Num;
    int xBegin, xEnd, yBegin, yEnd;
    MandelBrotThread * createdThread[MB_THREADS_NUM + 1];
    //(void *) (MandelBrotGen::*thrd_Entry) (void *) = NULL;

    //thrd_Entry = ;

    for( thrd_Num=0; thrd_Num < numBlksThreads; thrd_Num++)
    {
        CalculateThreadBounds( thrd_Num, &xBegin, &xEnd, &yBegin, &yEnd);
        createdThread[thrd_Num] = new MandelBrotThread(thrd_Num, xBegin, xEnd, yBegin, yEnd, this);

   }

    for( thrd_Num=0; thrd_Num < numBlksThreads; thrd_Num++)
    {
        if( (createdThread[thrd_Num])->GetThreadExecStatus())
        {
            if(pthread_join((createdThread[thrd_Num])->GetThreadID(), NULL) == 0)
            {
                //printf("\r\n Waiting for thread %d successfully", thrd_Num);
                //SDL_Flip(drawScreen);
                //SDL_Delay(100);
            }
            else
                printf("\r\n Pthread_joing failed");
        }
    }
    return thrd_Num;
}

/** @brief CalculateThreadBounds
  *
  * @todo: document this function
  */
void MandelBrotGen::CalculateThreadBounds(int threadNum, int * xBegin, int * xEnd, int * yBegin, int * yEnd)
{
    *(xBegin) = (threadNum % xDiv) * (xRes / xDiv);
    *(xEnd) = ((threadNum % xDiv) + 1) * (xRes / xDiv) ;

    *(yBegin) = (threadNum / yDiv) * (yRes / yDiv);
    *(yEnd) = ((threadNum / yDiv) + 1) * (yRes / yDiv);
}

/** @brief ~MandelBrotGen
  *
  * @todo: document this function
  */
MandelBrotGen::~MandelBrotGen()
{

}

/** @brief GetYRes
  *
  * @todo: document this function
  */
int MandelBrotGen::GetXRes()
{
    return xRes;
}

/** @brief GetXRes
  *
  * @todo: document this function
  */
int MandelBrotGen::GetYRes()
{
    return yRes;
}

/** @brief OnPixel
  *
  * @todo: document this function
  */
void MandelBrotGen::OnPixel(int x, int y, int iter)
{
    //printf("\r\n Set Pixel ON[%d,%d]", x, y);
    SetPixelWithAttrib( x, y, IN_MBSET, iter);
}

/** @brief OffPixel
  *
  * @todo: document this function
  */
void MandelBrotGen::OffPixel(int x, int y, int iter)
{
    //printf("\r\n Set Pixel OFF[%d,%d]", x, y);
    SetPixelWithAttrib( x, y, OUT_MBSET, iter);
}

/** @brief SetPixelWithAttrib
  *
  * @todo: document this function
  */
void MandelBrotGen::SetPixelWithAttrib(int x, int y, Attrib enAttrib, int iter)
{
    int ytimesw;
    int bytesPerPix;
    Uint16 * pixMem;
    Uint32 colour;
    int r, g, b;

    bytesPerPix =  drawScreen->format->BytesPerPixel;
    ytimesw = y*drawScreen->pitch/bytesPerPix;

    r = (iter%5)*50;
    g = (iter/2)*10;
    b = (iter+1)/9*100;

    colour = SDL_MapRGB(drawScreen->format, r, g, b);

    pixMem = (Uint16 *) drawScreen->pixels + ytimesw + x;

    //printf("\r\n [%d,%d]", x,ytimesw);


    *pixMem = colour;
    //printf("\r\n [%d,%d, %x]", x,ytimesw, pixMem);

    //SDL_Flip(drawScreen);

    //SDL_Delay(10);

}

/** @brief GetBIncrement
  *
  * @todo: document this function
  */
double MandelBrotGen::GetAIncrement()
{
    return a_increment;
}

/** @brief GetAIncrement
  *
  * @todo: document this function
  */
double MandelBrotGen::GetBIncrement()
{
    return b_increment;
}




