typedef struct {
  char *text;
  SDL_Surface *img;
  SDL_Rect pos;
  void (*function)(SDL_Surface *screen);
} Button;


Button initButton(int x, int y, char text[100], char url[100], void (*function)()){
  Button button;
  button.pos.x = x;
  button.pos.y = y;
  button.text = text;
  button.img = IMG_Load(url);
  button.function = function;
  return button;
}


void displayButton(Button button, SDL_Surface *screen){
  SDL_BlitSurface(button.img, NULL, screen, &button.pos);
  SDL_Flip(screen);
}

void displayMenu(Button menu[], SDL_Surface *screen, int nbButton){
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  for (int i = 0; i < nbButton; i++) {
    displayButton(menu[i], screen);
  }
  SDL_Flip(screen);
}

int clickButton(Button button, SDL_Event event){
  if(event.button.button == SDL_BUTTON_LEFT
        && event.button.x > button.pos.x
        && event.button.x < button.pos.x + button.img->w
        && event.button.y > button.pos.y
        && event.button.y < button.pos.y + button.img->h)
        return 1;
  return 0;
}

int waitEvent(Button menu[], SDL_Surface *screen, int nbButton){
  int loop = 1;
  SDL_Event event;
  SDL_Rect pos;

  while (loop) {
    SDL_WaitEvent(&event);
    switch(event.type) {
      case SDL_QUIT:
            SDL_Quit();
            exit(0);
      case SDL_MOUSEBUTTONUP:
        for(int i=0; i < nbButton; i++){
          if (clickButton(menu[i], event)){
                (*menu[i].function)(screen);
                break;
          }
        }
    }
  }
}
