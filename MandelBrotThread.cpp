#include "MandelBrotCommon.h"
#include "MandelBrotGen.h"
#include "MandelBrotThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

MandelBrotThread::MandelBrotThread()
{
    //ctor
}

MandelBrotThread::~MandelBrotThread()
{
    //dtor
}

/** @brief MandelBrotThread
  *
  * @todo: document this function
  */
 MandelBrotThread::MandelBrotThread(int threadNum, int xBegin, int xEnd, int yBegin, int yEnd, MandelBrotGen * poMandelBrotGen)
{
    int result;

    this->threadNum = threadNum;
    threadStatus = false;

    this->xBegin = xBegin;
    this->xEnd = xEnd;
    this->yBegin = yBegin;
    this->yEnd = yEnd;

    this->poMandelBrotGen = poMandelBrotGen;

    a_thd_begin = ( xBegin * poMandelBrotGen->GetAIncrement() ) +  A_BEGIN;
    a_thd_end = ( xEnd * poMandelBrotGen->GetAIncrement() ) +  A_BEGIN;
    b_thd_begin = ( yBegin * poMandelBrotGen->GetBIncrement() ) + B_BEGIN;
    b_thd_end = ( yEnd * poMandelBrotGen->GetBIncrement() ) + B_BEGIN;

    result = pthread_create( &threadID, 0, MandelBrotThread::ThreadEntry, this);
    if (result != 0)
    {
        printf("\r\n Creating thread : %d failed", threadNum);

        threadStatus = false;
        pthread_detach(threadID);
    }
    else
        threadStatus = true;
}

/** @brief ThreadEntry
  *
  * @todo: document this function
  */
void* MandelBrotThread::ThreadEntry(void * arg)
{
    return ( (MandelBrotThread *) arg)->ExecuteMandelBrotGen();
}

/** @brief GetThreadExecStatus
  *
  * @todo: document this function
  */
bool MandelBrotThread::GetThreadExecStatus()
{
    return threadStatus;
}

/** @brief GetThreadID
  *
  * @todo: document this function
  */
pthread_t MandelBrotThread::GetThreadID()
{
    return threadID;
}

/** @brief ExecuteMandelBrotGen
  *
  * @todo: document this function
  */
void* MandelBrotThread::ExecuteMandelBrotGen()
{

    printf("\r\n Thread[%d] : Begin [%d,%d] --> BeginAB[%f,%f], End[%d,%d] --> EndAB[%f,%f]",
        threadNum, xBegin, yBegin, a_thd_begin, b_thd_begin, xEnd, yEnd, a_thd_end, b_thd_end);

    StartMandelBrotGen();
    printf("\r\n");
#if 1
        /*while(1)
        {
            ;//printf("%d ", threadNum);
        }*/
#endif
    return NULL;
}

/** @brief StartMandelBrotGen
  *
  * @todo: document this function
  */
void MandelBrotThread::StartMandelBrotGen()
{
    double a_increment, b_increment;
    double aVal, bVal;
    int xVal, yVal;
    int noOfIter;

    xVal = xBegin;
    yVal = yBegin;

    a_increment = poMandelBrotGen->GetAIncrement();
    b_increment = poMandelBrotGen->GetBIncrement();

    for( aVal = a_thd_begin; aVal <= a_thd_end; aVal += a_increment, xVal++ )
    {
        for( bVal = b_thd_begin; bVal <= b_thd_end; bVal += b_increment, yVal++ )
        {
            noOfIter = CheckMagForMBSet( aVal, bVal);
            if( noOfIter > ITERATION )
            {
                //if(threadNum == 0 || threadNum == 2)
                    poMandelBrotGen->OnPixel( xVal, yVal, noOfIter);
                //printf("\r\n Thread%d : [%d,%d] for [%f,%f] in [%d]", threadNum, xVal, yVal, aVal, bVal, noOfIter);
            }
            else
            {
                //if(threadNum == 0 || threadNum == 2)
                    poMandelBrotGen->OffPixel( xVal, yVal, noOfIter);
                //printf("\r\n Thread%d : [%d,%d] for [%f,%f] in [%d]", threadNum, xVal, yVal, aVal, bVal,noOfIter);
            }
            if( (yVal > yEnd))
                break;
        }
        if( (xVal > xEnd))
            break;
        yVal = yBegin;
    }
}

/** @brief CheckMagForMBSet
  *
  * @todo: document this function
  */
int MandelBrotThread::CheckMagForMBSet(double aVal, double bVal)
{
    double x = 0.0;
    double y = 0.0;
    double xTemp = 0.0;
    int iterateVal = 0;

    do
    {
        xTemp = RZn( x, y, aVal);
        y = iZn( x, y, bVal);

        x = xTemp;

        if(iterateVal ++ > ITERATION)
        {
            break;
        }

    }while( MAG(x,y) <= ( (MAX_MAG) * (MAX_MAG) ) );

    return iterateVal;
}








