#include "view_page.h"
#include <exception>

gamekid::memory::view_page::view_page(const byte * view) : _view(view){
}

byte gamekid::memory::view_page::load(byte offset) {
    return _view[offset];
}

void gamekid::memory::view_page::store(byte offset, byte value) {
    throw std::exception("Cannot store");
}
