#pragma once

#include <type_traits>


namespace di::Details
{

template<template<typename...> class Base, typename Derived>
struct IsBaseOfTemplate
{
    template<typename... Ts>
    static constexpr std::true_type test(Base<Ts...> *);
    static constexpr std::false_type test(...);

    using type = decltype(test(std::declval<Derived*>()));
public:
    static constexpr bool value = type::value;
};

} // namespace di::Details
