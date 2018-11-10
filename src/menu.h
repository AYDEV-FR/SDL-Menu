typedef struct {
  char *text;
  SDL_Surface *surface;
  SDL_Rect pos;
  SDL_Color rgb;
  void (*function)(SDL_Surface *screen);
} Button;


/* PROTOTYPAGE */
SDL_Color colorConverter(unsigned long hexValue);

void initMenu(char font_name[]);

void displayImg(SDL_Surface *screen, int x, int y, char url[]);
void displayColor(SDL_Surface *screen, int hexColor);

SDL_Surface *initText(char text[], int fontSize, int hexColorFont, int params);
void displayText(SDL_Surface *surface, SDL_Surface *textSurface, int x, int y);
void displayParagraph(SDL_Surface *surface, SDL_Surface **textSurface, int x, int y, int nbLine);
void displayParagraphCenter(SDL_Surface *surface, SDL_Surface **textSurface, int y, int nbLine);

Button initButtonImgText(int x, int y, char text[], int fontSize,
  int hexColor, int params, char url[100], void (*function)());

Button initButtonImg(int x, int y, char url[100], void (*function)());
Button initButtonRect(
      int x, int y, int w, int h,
      int hexColorRect, char text[], int fontSize, int hexColorFont,
      int params, void (*function)()
    );

void displayButton(Button button, SDL_Surface *screen);
void displayMenu(Button menu[], SDL_Surface *screen, int nbButton);

int clickButton(Button button, SDL_Event event);
int waitEvent(Button menu[], SDL_Surface *screen, int nbButton);




/* GLOBAL VAR */
char *fontName = NULL;


SDL_Color colorConverter(unsigned long hexValue) {
  SDL_Color rgbColor;
  rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
  rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
  rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte
  return rgbColor;
}

void initMenu(char font_name[]){
  fontName = font_name;
  if(TTF_Init() == -1) {
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

void displayImg(SDL_Surface *screen, int x, int y, char url[]){
  SDL_Surface *img = IMG_Load(url);
  SDL_Rect position = {x, y};
  SDL_BlitSurface(img, NULL, screen, &position);
  SDL_FreeSurface(img);
  SDL_Flip(screen);
}

void displayColor(SDL_Surface *screen, int hexColor){
  SDL_Color color = colorConverter(hexColor);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, color.r, color.g, color.b));
  SDL_Flip(screen);
}


SDL_Surface *initText(char text[], int fontSize, int hexColorFont, int params){
  TTF_Font *font;
  SDL_Surface *textSurface;

  font = TTF_OpenFont(fontName, fontSize);
  TTF_SetFontStyle(font, params);
  textSurface = TTF_RenderText_Blended(font, text, colorConverter(hexColorFont));
  TTF_CloseFont(font);

  return textSurface;
}

void displayText(SDL_Surface *surface, SDL_Surface *textSurface, int x, int y){
  SDL_Rect position;
  position.x = x;
  position.y = y;
  SDL_BlitSurface(textSurface, NULL, surface, &position);
  SDL_FreeSurface(textSurface);
  SDL_Flip(surface);
}

void displayParagraph(SDL_Surface *surface, SDL_Surface **textSurface, int x, int y, int nbLine){
  for(int i = 0; i < nbLine; i++){
      displayText(surface, textSurface[i],
        x,
        y + textSurface[i]->h * i);
  }
}

void displayParagraphCenter(SDL_Surface *surface, SDL_Surface **textSurface, int y, int nbLine){
  for(int i = -1; i < nbLine - 1; i++){
      displayText(surface, textSurface[i+1],
        (surface->w)/2-(textSurface[i+1]->w)/2,
        y + textSurface[i+1]->h * i);
  }
}

Button initButtonImgText(int x, int y, char text[], int fontSize, int hexColor, int params, char url[100], void (*function)()){
  Button button;
  button.pos.x = x;
  button.pos.y = y;
  button.text = text;
  button.surface = IMG_Load(url);
  button.function = function;

  SDL_Surface *textSurface = initText(text, fontSize, hexColor, params);
  displayText(button.surface, textSurface,
    ((button.surface->w)/2)-((textSurface->w)/2),
    ((button.surface->h)/2)-((textSurface->h)/2));

  return button;
}

Button initButtonImg(int x, int y, char url[100], void (*function)()){
  Button button;
  button.pos.x = x;
  button.pos.y = y;
  button.surface = IMG_Load(url);
  button.function = function;

  return button;
}

Button initButtonRect(
      int x, int y, int w, int h,
      int hexColorRect, char text[], int fontSize, int hexColorFont,
      int params, void (*function)()
      ){


  Button button;
  button.pos.x = x;
  button.pos.y = y;
  button.text = text;
  button.surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
  button.function = function;

  SDL_Color color = colorConverter(hexColorRect);
  SDL_FillRect(button.surface, NULL, SDL_MapRGB(button.surface->format, color.r, color.g, color.b));
  SDL_Surface *textSurface = initText(text, fontSize, hexColorFont, params);
  displayText(button.surface, textSurface,
    ((button.surface->w)/2)-((textSurface->w)/2),
    ((button.surface->h)/2)-((textSurface->h)/2));
  return button;
}


void displayButton(Button button, SDL_Surface *screen){
  SDL_BlitSurface(button.surface, NULL, screen, &button.pos);
  SDL_FreeSurface(button.surface);
  SDL_Flip(screen);
}

void displayMenu(Button menu[], SDL_Surface *screen, int nbButton){
  for (int i = 0; i < nbButton; i++) {
    displayButton(menu[i], screen);
  }
}

int clickButton(Button button, SDL_Event event){
  if(event.button.button == SDL_BUTTON_LEFT
        && event.button.x > button.pos.x
        && event.button.x < button.pos.x + button.surface->w
        && event.button.y > button.pos.y
        && event.button.y < button.pos.y + button.surface->h)
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
              //for(int j=0; j < nbButton; j++) SDL_FreeSurface(menu[j].surface);
              (*menu[i].function)(screen);
              break;
          }
        }
    }
  }
}
