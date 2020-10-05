#pragma once

#include <type_traits>


namespace di::Details
{

//template <template <typename...> class C, typename...Ts>
//std::true_type is_base_of_template_impl(const C<Ts...>*);

//template <template <typename...> class C>
//std::false_type is_base_of_template_impl(...);

//template <typename T, template <typename...> class C>
//using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));

template < template <typename...> class base,typename derived>
struct is_base_of_template_impl
{
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...> *);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template < template <typename...> class base,typename derived>
using is_base_of_template = typename is_base_of_template_impl<base,derived>::type;

} // namespace di::Details
