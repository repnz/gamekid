#include "lcd.h"

bool gamekid::io::lcd::enabled() const {
    return _enabled;
}

void gamekid::io::lcd::enabled(bool value) {
    _enabled = value;
}

bool gamekid::io::lcd::window_enabled() const {
    return _window_enabled;
}

void gamekid::io::lcd::window_enabled(bool value) {
    _window_enabled = value;
}
