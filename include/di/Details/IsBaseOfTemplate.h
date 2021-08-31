#pragma once

#include <type_traits>


namespace di::Details
{

template<template<typename...> class Base, typename Derived>
struct IsBaseOfTemplateImpl
{
    template<typename... Ts>
    static constexpr std::true_type test(const Base<Ts...> *);
    static constexpr std::false_type test(...);

    using type = decltype(test(std::declval<Derived*>()));
};

template<template<typename...> class Base, typename Derived>
using IsBaseOfTemplate = typename IsBaseOfTemplateImpl<Base, Derived>::type;

} // namespace di::Details
