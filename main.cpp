#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Mandelbrot.h"

const float FPS = 60.0;

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   al_init_primitives_addon();

   display = al_create_display(800, 600);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      return -1;
   }
   
   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   
   while(1)
   {
      al_clear_to_color(al_map_rgb(0,0,0));
      al_flip_display();

      Mandelbrot();
      al_flip_display();

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
   }

   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}
