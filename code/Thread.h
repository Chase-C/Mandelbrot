#ifndef THREAD_H
#define THREAD_H

#include <allegro5/allegro.h>

class DISPLAY_DATA
{
    public:
        ALLEGRO_MUTEX *mutex;
        ALLEGRO_COND *cond;

        int sizeX, sizeY;

        double zoomXmin,
               zoomXmax,
               zoomYmin,
               zoomYmax;

        DISPLAY_DATA() : mutex(al_create_mutex()),
                         cond(al_create_cond()),
                         sizeX(800),
                         sizeY(600),
                         zoomXmin(-2.2),
                         zoomXmax(1.2),
                         zoomYmin(-1.7),
                         zoomYmax(1.7) {}

        ~DISPLAY_DATA() {
            al_destroy_mutex(mutex);
            al_destroy_cond(cond);
        }
};

void *CreateDisplay(ALLEGRO_THREAD *thr, void *arg);

#endif
