#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Mandelbrot.h"
#include "Thread.h"

using namespace std;

ALLEGRO_EVENT_QUEUE *AllegroInit();

template <typename T>
T GetVal(string str, const char *format, T curr)
{
    printf("New %s: ", str.c_str());

    T value;
    int scanCount = scanf(format, &value);

    if(scanCount != 1) {
        fprintf(stderr, "Bad number\n\n");
        return curr;
    }

    return value;
};

void EditWindowSize(DISPLAY_DATA *data)
{
    al_lock_mutex(data->mutex);
    data->sizeX = GetVal<int>("window width", "%i", data->sizeX);
    data->sizeY = GetVal<int>("window height", "%i", data->sizeY);
    al_unlock_mutex(data->mutex);
}

void EditZoom(DISPLAY_DATA *data)
{
    al_lock_mutex(data->mutex);
    data->zoomXmin = GetVal<double>("minimum X", "%lg", data->zoomXmin);
    data->zoomXmax = GetVal<double>("maximum X", "%lg", data->zoomXmax);
    data->zoomYmin = GetVal<double>("minimum Y", "%lg", data->zoomYmin);
    data->zoomYmax = GetVal<double>("maximum Y", "%lg", data->zoomYmax);
    al_unlock_mutex(data->mutex);
}

int main(int argc, char **argv)
{
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    vector<ALLEGRO_THREAD*> threads;
    DISPLAY_DATA *data = new DISPLAY_DATA();

    bool run = true;
    while(run) {
        printf("Current Window Size: %i x %i\n", data->sizeX, data->sizeY);
        printf("Current Zoom: [%f, %f] [%f, %f]\n\n", data->zoomXmin, data->zoomYmin,
                                                          data->zoomXmax, data->zoomYmax);
        printf("1) Edit Window Size\n");
        printf("2) Edit Zoom\n");
        printf("3) Generate Fractal\n");
        printf("4) Exit\n> ");

        int option;
        int scanCount = scanf("%i", &option);
        if(scanCount == EOF) {
            break;
        } else if(scanCount != 1) {
            fprintf(stderr, "Not valid input\n\n");
            fflush(stdin);
            continue;
        }

        switch(option) {
            case 1:
                EditWindowSize(data);                  
                break;
            case 2:
                EditZoom(data);
                break;
            case 3:
                threads.push_back(al_create_thread(CreateDisplay, data));
                al_start_thread(threads.back());
                break;
            case 4:
                run = false;
                break;
        }

        for(int i = 0; i < threads.size(); i++) {
            if(al_get_thread_should_stop(threads[i])) {
                al_destroy_thread(threads[i]);
                threads.erase(threads.begin() + i);
            }
        }
    }

    for(ALLEGRO_THREAD *thr : threads) {
        al_set_thread_should_stop(thr);
        al_destroy_thread(thr);
    }

    return 0;
}
