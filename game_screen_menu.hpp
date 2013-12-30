#ifndef GAME_SCREEN_MENU_HPP
#define GAME_SCREEN_MENU_HPP

#include <SDL.h>
#include "game.hpp"

void game_screen_menu(Game &game)
{
  
  while(SDL_PollEvent(&game.event))
  {
    if(game.event.type== SDL_QUIT)
    {
      game.run= false;
      break;
    }
    if(game.event.type== SDL_KEYDOWN)
    {
      switch(game.event.key.keysym.sym)
      {
        case SDLK_F4:
          if(game.event.key.keysym.mod & KMOD_LALT) game.run= false;
          break;
        default:
          break;
      }
    }
  }
}

#endif

