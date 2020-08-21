#pragma once

#include <type_traits>


namespace di::Details
{

#define GENERATE_HAS_MEMBER(member)                                               \
                                                                                  \
template < class T >                                                              \
class HasMember_##member                                                          \
{                                                                                 \
    using Yes = char[2];                                                          \
    using No = char[1];                                                           \
                                                                                  \
    struct Fallback { int member; };                                              \
    struct Derived : T, Fallback {};                                              \
                                                                                  \
    template < class U >                                                          \
    static No& test ( decltype(U::member)* );                                     \
    template < typename U >                                                       \
    static Yes& test ( U* );                                                      \
                                                                                  \
public:                                                                           \
    static constexpr bool RESULT = sizeof(test<Derived>(nullptr)) == sizeof(Yes); \
};                                                                                \
                                                                                  \
template < class T >                                                              \
struct has_member_##member                                                        \
: public std::integral_constant<bool, HasMember_##member<T>::RESULT>              \
{}

GENERATE_HAS_MEMBER(di); // generates has_member_di

} // namespace di::Details
