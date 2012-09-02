#if 0
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#endif

#include "SDL.h"
#include <stdio.h>
#include "MandelBrotGen.h"

#ifdef TEST_JUNK
void SetPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{

    Uint16 * pixMem;
    int ticks;

    ticks=SDL_GetTicks();

    colour = SDL_MapRGB(screen->format, r, g, b);

    pixMem = (Uint16 *) screen->pixels + y + x;

    //*pixMem = colour;

    *pixMem = /*x*x + y*y + */ticks;
}
#endif

int main ( int argc, char** argv )
{

    SDL_Surface* screen = NULL;
    SDL_Event capturedEvent;
    const SDL_VideoInfo * videoInfo = NULL;
    int systemX, systemY;
    Uint8 bitsPerPix;
    MandelBrotGen * poMBGen;
    bool quit = false;

    #ifdef TEST_JUNK
    int x, y;
    int i;
    int ytimesw;
    int bytesPerPix;

    #endif

    printf("\r\n Starting MandelBrot...");


    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }


    videoInfo = SDL_GetVideoInfo();

    systemX = videoInfo->current_w;
    systemY = videoInfo->current_h;
    bitsPerPix = videoInfo->vfmt->BitsPerPixel;


    //Set up screen based on system parameters
    screen = SDL_SetVideoMode( systemX, systemY, bitsPerPix, SDL_SWSURFACE);

    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n", systemX, systemY, SDL_GetError());
        return 1;
    }

    poMBGen = new MandelBrotGen(1920,1080, screen);
    poMBGen->StartGeneratingMB();

    SDL_Flip(screen);

    while( !quit )
    {
        if( SDL_PollEvent( &capturedEvent ) )
        {
            switch (capturedEvent.type)
            {
                case SDL_QUIT:
                    //Quit the program
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if( capturedEvent.button.button == SDL_BUTTON_LEFT )

                    printf("\r\n Mouse Butt down");
                    break;

                case SDL_MOUSEBUTTONUP:
                    printf("\r\n Mouse Butt up");
                    break;

                case SDL_KEYUP:
                    printf("\r\n Mouse Butt down");
                    break;
            }
        }
    }

    SDL_Quit();

    printf("\r\n All done here...");

    #ifdef TEST_JUNK
    printf("\r\n Bytes per pix : %d", bytesPerPix);
    #endif

    //
    /*


    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    =SDL_GetVideoInfo();
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_SWSURFACE);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;

    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)/home/pi/Dev/HelloMandelBrot/src
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    */
    return 0;
}
