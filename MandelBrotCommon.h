#ifndef MANDELBROTCOMMON_H_INCLUDED
#define MANDELBROTCOMMON_H_INCLUDED

#define RZn(x,y,a) ( ((x)*(x)) - ((y)*(y)) + (a) )
#define iZn(x,y,b) ( (2*(x)*(y)) +(b))
#define MAG(x,y) ( ((x)*(x)) + ((y)*(y)) )

#define ITERATION (200.0)

#define A_BEGIN (-2.5)
#define A_END   (1.0)
#define B_BEGIN (-1.0)
#define B_END   (1.0)

#define MAX_MAG (20.0)


#endif // MANDELBROTCOMMON_H_INCLUDED
