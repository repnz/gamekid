#pragma once
#include <string>
#include <sstream>

namespace string_tools
{
    template <typename Container, typename OutputStream>
    void join(const Container& container, const std::string& seperator, OutputStream& strm)
    {
        int i = 0;

        for (const auto& item : container)
        {
            if (i != 0)
                strm << seperator;
            strm << item;
            ++i;
        }
    }

    template <typename Container>
    std::string join(const Container& container, const std::string& seperator = ", ")
    {
        std::ostringstream ss;
        join<Container, std::ostringstream>(container, seperator, ss);
        return ss.str();
    }
}
