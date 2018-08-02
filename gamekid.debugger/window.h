#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <array>

namespace gamekid::debugger {
    struct point {
        int x, y;

        point(int x, int y) : x(x), y(y) {
        }
    };

    const std::array<SDL2pp::Color, 4> colors = {
        SDL2pp::Color { 0xFF, 0xFF, 0xFF },
        SDL2pp::Color { 0x99, 0x99, 0x99 },
        SDL2pp::Color { 0x55, 0x55, 0x55 },
        SDL2pp::Color { 0x00, 0x00, 0x00 }
    };

    class window {
    private:
        SDL2pp::SDL _sdl;
        SDL2pp::Window _window;
        SDL2pp::Renderer _renderer;
    public:
        window();
        bool poll_events();
        void put_pixel(point location, SDL2pp::Color value);
        void render();
        void show();
    };
}

