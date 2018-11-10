void menu_main(SDL_Surface *screen);
void settings(SDL_Surface *screen);
void test(SDL_Surface *screen);

void menu_main(SDL_Surface *screen){
  int btnHeight = 120, btnWidth = 322;
  int xm = (screen->w)/2 - btnWidth/2;

  Button menu[3] = {

    initButtonImg(xm, 2 * (btnHeight  + 10), "../img/settings.png", settings),
    initButtonRect(xm, btnHeight  + 10, btnWidth, btnHeight, 0xFFFF00, "Play !", 42, 0x000000, TTF_STYLE_ITALIC | TTF_STYLE_BOLD, test),
    initButtonRect(xm, 3 * (btnHeight + 10), btnWidth, btnHeight, 0x000000, "EXIT", 42, 0xFFFFFF, TTF_STYLE_BOLD, exit),

  };

  SDL_Surface *text = initText("Jeu : Dame chinoise", 36, 0x000000, TTF_STYLE_UNDERLINE);

  displayColor(screen, 0xFFFFFF);
  displayImg(screen, 50, 100, "../img/background.png");
  displayText(screen, text, (screen->w)/2 - (text->w)/2 , 40);
  displayMenu(menu, screen, 3);
  printf("%d \n", menu[0].surface->h);
  waitEvent(menu, screen, 3);
}


void settings(SDL_Surface *screen){
  int btnHeight = 120, btnWidth = 322;
  int xm = (screen->w)/2 - btnWidth/2;

  Button menu[3] = {

    initButtonImgText(xm, 100, "RETOUR", 36, 0x000000, 0, "../img/back.png", menu_main),
    initButtonImgText(xm, 250, "REGLES", 36, 0x000000, 0, "../img/rules.png", menu_main),
    initButtonImg(xm, 450, "../img/exit.png", exit),

  };
  displayColor(screen, 0xFF0000);
  displayMenu(menu, screen, 3);
  waitEvent(menu, screen, 3);
}

void test(SDL_Surface *screen){


  Button menu[2] = {

    initButtonImg(50, (screen->h) - 100, "../img/back.png", settings),
    initButtonImg((screen->w) - 250, (screen->h) - 100, "../img/exit.png", exit)
    //initButtonImgText(400, 300, "Yolo", 36, 0xFFFFFF, 0, "../img/exit.png", exit),

  };

  SDL_Surface *text[6] = {
    initText("Regles du jeu", 36, 0x000000, TTF_STYLE_UNDERLINE),
    initText("blablaaaaaaa", 12, 0x000000, 0),
    initText("blablaaaaaaa", 12, 0x000000, 0),
    initText("blablaaaaaaa", 12, 0x000000, 0),
    initText("blablaaaaa", 12, 0x000000, 0),
    initText("blablaa", 12, 0x000000, 0)
  };

  displayColor(screen, 0xFF00FF);
  displayMenu(menu, screen, 2);
  displayParagraphCenter(screen, text, 60, 6);
  waitEvent(menu, screen, 2);
}
