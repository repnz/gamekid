#include "files.h"
#include <fstream>

std::vector<byte> gamekid::utils::files::read_file(const std::string & fileName) {
    std::ifstream f(fileName, std::ios::binary | std::ios::in | std::ios::ate);
    int file_size = f.tellg();
    f.seekg(std::ios::beg);
    std::vector<byte> data(file_size);
    f.read((char*)data.data(), file_size);
    return data;
}
