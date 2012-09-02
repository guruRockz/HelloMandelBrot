#ifndef MANDELBROTGEN_H
#define MANDELBROTGEN_H

#include "SDL.h"
#include <math.h>

#define MANDEL_SET
/*
#define REALZn(x,y,a)     ((x*x)-(y*y)+a)
#define IMAGINARYZn(x,y,b)    ((2*x*y)+b)
#define ITERATION  400.0

#define MAGNITUDE(x,y) (((x*x) + (y*y)))
#define RESOL_X 1600
#define RESOL_Y 1000

#define A_MIN (-2.5)
#define A_MAX (1.0)
#define B_MIN (-1.0)
#define B_MAX (1.0)
*/
#define MB_THREADS_NUM 4

typedef enum{
    IN_MBSET,
    OUT_MBSET,
} Attrib;

class MandelBrotGen
{

    private:
        int xRes, yRes;
        int xDiv, yDiv;
        SDL_Surface * drawScreen;
        bool isInMandelBrotSet;
        int maxReqIncr;
        int mostReqIncr;
        int numBlksThreads;
        double a_increment;
        double b_increment;
        double curr_a_begin, curr_a_end;
        double curr_b_begin, curr_b_end;
        MandelBrotGen();
        void CalculateThreadBounds(int threadNum, int * xBegin, int * xEnd, int * yBegin, int * yEnd);
        void SetPixelWithAttrib(int x, int y, Attrib enAttrib, int iter);
        int CreateMBThreads();
    public:
        MandelBrotGen(int x_Res, int y_Res, SDL_Surface * screen);
        ~MandelBrotGen();
        bool ChkMandelBrotSet(double a, double b, int * reqIncrement);
        void StartGeneratingMB();
        void StartGeneratingMB(int xBegin, int yBegin, int xEnd, int yEnd);
        int GetXRes();
        int GetYRes();
        void OnPixel(int x, int y, int iter);
        void OffPixel(int x, int y, int iter);
        double GetAIncrement();
        double GetBIncrement();
        //static void * GenMandelBrotSetBlock(void * arg_Thrd_ID);
};

#endif // MANDELBROTGEN_H
