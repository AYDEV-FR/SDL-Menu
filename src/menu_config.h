void menu_main(SDL_Surface *screen);
void settings(SDL_Surface *screen);
void test(SDL_Surface *screen);

void menu_main(SDL_Surface *screen){
  Button menu[2] = {

    initButtonRect(200, 100, 200, 300, 0xFF0000, "TEXT", 12, 0x000000, TTF_STYLE_UNDERLINE, settings),
    initButtonImgText(400, 300, "Yolo", 36, 0xFFFFFF, TTF_STYLE_UNDERLINE, "../img/exit.png", exit),

  };

   SDL_Surface *text[2] = {
     initText("Jeu : Hex Game", 36, 0x000000, TTF_STYLE_ITALIC),
     initText("Jeu : Dame chinoise", 36, 0x000000, TTF_STYLE_UNDERLINE)
   };

  displayColor(screen, 0xFFFFFF);
  displayImg(screen, 0, 0, "../img/background.png");
  displayMenu(menu, screen, 2);
  displayParagraphCenter(screen, text, 20, 2);
  waitEvent(menu, screen, 2);
}


void settings(SDL_Surface *screen){
  Button menu[2] = {

    initButtonImg(0, 0, "../img/back.png", test),
    initButtonImgText(400, 300, "Yolo", 36, 0xFFFFFF, 0, "../img/exit.png", exit),

  };
  displayColor(screen, 0xFF0000);
  displayMenu(menu, screen, 2);
  waitEvent(menu, screen, 2);
}

void test(SDL_Surface *screen){
  Button menu[3] = {

    initButtonImg(0, 0, "../img/play.png", menu_main),
    initButtonImg(10, 100, "../img/back.png", settings),
    initButtonImgText(400, 300, "Yolo", 36, 0xFFFFFF, 0, "../img/exit.png", exit),

  };

  displayColor(screen, 0xFF00FF);
  displayMenu(menu, screen, 3);
  waitEvent(menu, screen, 3);
}
