#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

struct SDLResource
{
  SDLResource()
  {
    std::cout<< "SDL Init & Set Video Mode\n";
    int err= SDL_Init(SDL_INIT_EVERYTHING);
    if(err!= 0)
      throw std::runtime_error("Initializing SDL: "+ std::string(SDL_GetError()));

    auto video= SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    if(!video)
      throw std::runtime_error("Setting video mode: "+ std::string(SDL_GetError()));
  }

  ~SDLResource()
  {
    std::cerr<< "SDL Quit"<< std::endl;
    SDL_Quit();
  }
};

struct SDLTTFResource
{
  SDLTTFResource()
  {
    std::cout<< "TTF Init\n";
    int err= TTF_Init();
    if(err!= 0)
      throw std::runtime_error("Initializing SDL_ttf: "+ std::string(TTF_GetError()));
  }

  ~SDLTTFResource()
  {
    std::cerr<< "TTF Quit"<< std::endl;
    TTF_Quit();
  }
};

struct SDLTTFFontResource
{
  TTF_Font* font;
  typedef std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> FontResource;
  FontResource menu_new_game;
  FontResource menu_quit;
  FontResource menu_new_game_selected;
  FontResource menu_quit_selected;

  SDLTTFFontResource()
  : menu_new_game(0, &SDL_FreeSurface)
  , menu_quit(0, &SDL_FreeSurface)
  , menu_new_game_selected(0, &SDL_FreeSurface)
  , menu_quit_selected(0, &SDL_FreeSurface)
  {
    std::cout<< "TTF OpenFont\n";
    font= TTF_OpenFont("fonts/freefont-20120503/FreeMonoBoldOblique.ttf", 16);
    if(!font)
      throw std::runtime_error("Opening font: "+ std::string(TTF_GetError()));

    SDL_Color yellow{ 255, 255, 0 };
    menu_new_game= FontResource(TTF_RenderUTF8_Blended(font, "New Game", yellow), &SDL_FreeSurface);
    if(!menu_new_game)
      throw std::runtime_error("Rendering font: "+ std::string(TTF_GetError()));
    menu_quit= FontResource(TTF_RenderUTF8_Blended(font, "Quit", yellow), &SDL_FreeSurface);
    if(!menu_quit)
      throw std::runtime_error("Rendering font: "+ std::string(TTF_GetError()));
    
    SDL_Color green{ 0, 255, 0 };
    menu_new_game_selected= FontResource(TTF_RenderUTF8_Blended(font, "New Game", green), &SDL_FreeSurface);
    if(!menu_new_game_selected)
      throw std::runtime_error("Rendering font: "+ std::string(TTF_GetError()));
    menu_quit_selected= FontResource(TTF_RenderUTF8_Blended(font, "Quit", green), &SDL_FreeSurface);
    if(!menu_quit_selected)
      throw std::runtime_error("Rendering font: "+ std::string(TTF_GetError()));
  }

  ~SDLTTFFontResource()
  {
    std::cerr<< "TTF Close Font"<< std::endl;
    TTF_CloseFont(font);
  }
};

struct GameScreenMenu
{
  int selected;
  GameScreenMenu()
  : selected(0)
  {}
};

struct Game
{
  enum class Screen
  {
    MENU, LOBBY, QUIT
  };

  Screen screen;
  bool run;
  SDLResource sdl;
  SDLTTFResource ttf;
  SDLTTFFontResource font;
  SDL_Event event;

  Game()
  : screen(Screen::MENU)
  , run(true)
  {}
};

#endif

