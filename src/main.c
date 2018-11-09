#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "menu_config.h"

void wait();

void hello(){
  printf("Hello World ! \n");
}

void main(){
  SDL_Surface *screen = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

  SDL_Flip(screen);

  initMenu("arial.ttf");


  SDL_Flip(screen);

  menu_main(screen);

  //wait();
  SDL_Quit();
  exit(0);
}




void wait(){
  SDL_Event event;
  int continuer = 1;

  while (continuer)
  {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
        case SDL_QUIT:
          continuer = 0;
          break;
      }
  }
}
