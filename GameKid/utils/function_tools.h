#pragma once
#include <variant>
#include <tuple>
#include <utility>

namespace function_tools
{   
    template<typename Function, typename Tuple, size_t ... I>
    auto forward_tuple(Function f, Tuple t, std::index_sequence<I ...>)
    {
        return f(std::get<I>(t) ...);
    }

    template<typename Function, typename Tuple>
    auto forward_tuple(Function f, Tuple t)
    {
        static constexpr auto size = std::tuple_size<Tuple>::value;
        return forward_tuple(f, t, std::make_index_sequence<size>{});
    }


    template<std::size_t I = 0, typename FuncT, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
        for_each(std::tuple<Tp...> &, FuncT) // Unused arguments are given no names.
    { }

    template<std::size_t I = 0, typename FuncT, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
        for_each(std::tuple<Tp...>& t, FuncT f)
    {
        f(std::get<I>(t));
        for_each<I + 1, FuncT, Tp...>(t, f);
    }
}