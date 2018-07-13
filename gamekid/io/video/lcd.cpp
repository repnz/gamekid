#include "lcd.h"

bool gamekid::io::video:: lcd::enabled() const {
    return _enabled;
}

void gamekid::io::video::lcd::enabled(bool value) {
    _enabled = value;
}

bool gamekid::io::video::lcd::window_enabled() const {
    return _window_enabled;
}

void gamekid::io::video::lcd::window_enabled(bool value) {
    _window_enabled = value;
}
