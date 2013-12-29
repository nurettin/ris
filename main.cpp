#include <SDL.h>
#include <memory>
#include <stdexcept>

template <typename F1, typename F2>
struct Scope
{
  F2 f2;
  Scope(F1 f1, F2 f2): f2(f2) { f1(); }
  ~Scope(){ f2(); }
};

template <typename F1, typename F2>
Scope<F1, F2> make_scope(F1 f1, F2 f2)
{
  return Scope<F1, F2>(f1, f2);
}

int main()
{
  auto sdl= make_scope([]{ 
    int err= SDL_Init(SDL_INIT_VIDEO);
    if(err!= 0)
      throw std::runtime_error("Error initializing SDL");
  }, []{ 
    SDL_Quit(); 
  });

  auto video= SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  if(video== 0)
    throw std::runtime_error("Error setting video mode");

  SDL_Event e;
  for(bool run= true; run; SDL_Delay(10))
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type== SDL_QUIT)
      {
        run= false;
        break;
      }
      if(e.type== SDL_KEYDOWN)
      {
        if(e.key.keysym.sym== SDLK_F4 && (e.key.keysym.mod & KMOD_LALT))
        {
          run= false;
          break;
        }
      }
    }
  }
}

