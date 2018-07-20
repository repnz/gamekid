#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <gamekid/utils/types.h>

namespace gamekid::debugger {
    struct point {
        int x, y;
    };

    namespace colors {
        const SDL2pp::Color A{ 0xFF, 0xFF, 0xFF };
        const SDL2pp::Color B{ 0x99, 0x99, 0x99 };
        const SDL2pp::Color C{ 0x55, 0x55, 0x55 };
        const SDL2pp::Color D{ 0x00, 0x00, 0x00 };
    }

    class window {
    private:
        SDL2pp::SDL _sdl;
        SDL2pp::Window _window;
        SDL2pp::Renderer _renderer;
    public:
        window();
        void poll_events();
        void put_pixel(point location, SDL2pp::Color value);
        void show();
    };
}

