#ifndef MANDELBROTTHREAD_H
#define MANDELBROTTHREAD_H

#include <pthread.h>

class MandelBrotThread
{
    private:
        int threadNum;
        pthread_t threadID;
        bool threadStatus;
        int xBegin, xEnd;
        int yBegin, yEnd;
        MandelBrotGen * poMandelBrotGen;
        double a_thd_begin, a_thd_end;
        double b_thd_begin, b_thd_end;
    public:
        MandelBrotThread(int threadNum, int xBegin, int xEnd, int yBegin, int yEnd, MandelBrotGen * poMandelBrotGen);
        virtual ~MandelBrotThread();
        pthread_t GetThreadID();
        bool GetThreadExecStatus();
    protected:
    private:
        MandelBrotThread();
        static void * ThreadEntry(void * arg);
        void * ExecuteMandelBrotGen();
        void StartMandelBrotGen();
        int CheckMagForMBSet(double a_val, double b_val);
};

#endif // MANDELBROTTHREAD_H
