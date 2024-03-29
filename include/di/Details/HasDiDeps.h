#pragma once

#include <type_traits>


namespace di::Details
{

template<class T>
class HasDiDeps
{
    template<class U>
    static std::true_type test(typename U::di_deps*);

    template<class U>
    static std::false_type test(U*);
public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

} // namespace di::Details
