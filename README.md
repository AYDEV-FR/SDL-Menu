# SDL-Menu
Mini Library for SDL Game in C

# Use

Compilation

     clear && gcc main.c `sdl-config --cflags --libs` -lSDL_image  && ./a.out

Classic main

    #include <stdio.h>
    #include <stdlib.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
    #include "menu.h"
    #include "menu_config.h"
    
    void main(){
      SDL_Surface *screen = NULL;
      SDL_Init(SDL_INIT_VIDEO);
      screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

      SDL_Flip(screen);

      menuMain(screen);

      SDL_Quit();
      exit(0);
    }
    
 Create menu
 
    void menuMain(SDL_Surface *screen){
      Button menu[2] = {

        initButton(200, 100, "Settings", "img/settings.png", settings),
        initButton(400, 300, "Exit", "img/exit.png", exit),

      };
      displayMenu(menu, screen, 2);
      waitEvent(menu, screen, 2);
    }

    void settings(SDL_Surface *screen){
          Button menu[2] = {

            initButton(200, 100, "Back", "img/back.png", menuMain),
            initButton(400, 300, "Exit", "img/exit.png", exit),

          };
          displayMenu(menu, screen, 2);
          waitEvent(menu, screen, 2);
    }
  
Init Button
 
    initButton(int x, int y, char text[100], char url[100], name of function launch)



## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2018 © <a href="http://des69u.fr" target="_blank">DES69U</a>.
