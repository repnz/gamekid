#include "window.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include "gamekid/utils/bytes.h"

namespace gamekid::debugger {

    const int screen_size = 256;
    const int zoom = 3;

    void window::poll_events() {
        SDL_Event e;
        
        while (!SDL_PollEvent(&e)) {   
        }
    }

    window::window() :
        _sdl(SDL_INIT_VIDEO),
        _window("gamekid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            screen_size*zoom, screen_size*zoom, 0),
        _renderer(_window, -1, SDL_RENDERER_ACCELERATED) {
        _renderer.Clear();
    }

    void window::render() {
        _renderer.Present();
    }

    void window::put_pixel(point location, SDL2pp::Color value) {
        _renderer.SetDrawColor(value);

        for (int y = location.y*zoom; y<location.y*zoom+zoom; ++y) {
            for (int x = location.x*zoom; x < location.x*zoom+zoom; ++x) {
                _renderer.DrawPoint(x, y);
            }
        }
    }

    void window::show() {
        _window.Show();
    }

}


