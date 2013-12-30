#include <memory>
#include <stdexcept>
#include <SDL.h>
#include <iostream>
#include "game.hpp"
#include "game_screen_menu.hpp"

int main()
{
  try
  {
    Game game;

    for(; game.run; SDL_Delay(10))
      switch(game.screen)
      {
        case Game::Screen::MENU:
          game_screen_menu(game);
          break;
        default:
          break;
      }
  } catch(std::runtime_error &ex) {
    std::cerr<< "Error: "<< ex.what()<< '\n';
  } catch(...) {
    std::cerr<< "An error occurred\n";
  }
}

