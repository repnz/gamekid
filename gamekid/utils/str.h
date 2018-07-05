#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace gamekid::utils::str
{
    template <typename Container, typename OutputStream>
    void join(const Container& container, const std::string& seperator, OutputStream& strm) {
        int i = 0;

        for (const auto& item : container) {
            if (i != 0)
                strm << seperator;
            strm << item;
            ++i;
        }
    }

    template <typename Container>
    std::string join(const Container& container, const std::string& seperator = ", "){
        std::ostringstream ss;
        join<Container, std::ostringstream>(container, seperator, ss);
        return ss.str();
    }

    template<typename Out>
    void split(const std::string &s, char delim, Out result)  {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }
    
    inline std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }
}
