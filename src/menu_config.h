void menu_main(SDL_Surface *screen);
void settings(SDL_Surface *screen);

void menu_main(SDL_Surface *screen){
  Button menu[2] = {

    initButton(200, 100, "Yolo", "../img/settings.png", settings),
    initButton(400, 300, "Yolo", "../img/exit.png", exit),

  };
  displayMenu(menu, screen, 2);
  waitEvent(menu, screen, 2);
}

void settings(SDL_Surface *screen){
  Button menu[2] = {

    initButton(0, 0, "Yolo", "../img/back.png", menu_main),
    initButton(400, 300, "Yolo", "../img/exit.png", exit),

  };

  displayMenu(menu, screen, 2);
  waitEvent(menu, screen, 2);
}
