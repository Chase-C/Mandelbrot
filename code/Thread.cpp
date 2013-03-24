#include <stdio.h>
#include <allegro5/allegro.h>

#include "Mandelbrot.h"
#include "Window.h"
#include "Thread.h"

ALLEGRO_DISPLAY *AllegroNewDisplay(int x, int y, ALLEGRO_EVENT_QUEUE *queue)
{
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE | ALLEGRO_NOFRAME);

    ALLEGRO_DISPLAY *display = al_create_display(x, y);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return NULL;
    }

    al_register_event_source(queue, al_get_display_event_source(display));

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    return display;
}

void *CreateDisplay(ALLEGRO_THREAD *thr, void *arg)
{
    DISPLAY_DATA *data = (DISPLAY_DATA*) arg;   
    ALLEGRO_DISPLAY *display;

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!queue) {
        fprintf(stderr, "failed to create event queue");
        return NULL;
    }

    al_lock_mutex(data->mutex);

    display = AllegroNewDisplay(data->sizeX, data->sizeY, queue);
    al_broadcast_cond(data->cond);

    // Define the size of the image
    Window<int> scr(0, data->sizeX, 0, data->sizeY);
    // Define the domain in which we test for points
    Window<double> fract(data->zoomXmin, data->zoomXmax, data->zoomYmin, data->zoomYmax);
    
    al_unlock_mutex(data->mutex);

    // Generate the fractal
    Mandelbrot(scr, fract);

    while(!al_get_thread_should_stop(thr)) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_set_thread_should_stop(thr);
            al_lock_mutex(data->mutex);
            al_broadcast_cond(data->cond);
            al_unlock_mutex(data->mutex);
            break;
        }       
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);
}
