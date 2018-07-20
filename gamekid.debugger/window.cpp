#include "window.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

namespace gamekid::debugger {

    void window::poll_events() {
        SDL_Event e;
        
        while (!SDL_PollEvent(&e)) {   
        }
    }

    window::window() :
        _sdl(SDL_INIT_VIDEO),
        _window("gamekid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0),
        _renderer(_window, -1, SDL_RENDERER_ACCELERATED) {
    }

    void window::put_pixel(point location, SDL2pp::Color value) {
        _renderer.SetDrawColor(value);
        _renderer.DrawPoint(location.x, location.y);
        _renderer.Present();
    }

    void window::show() {
        _window.Show();
    }

}


