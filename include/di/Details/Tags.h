#pragma once

#include <memory>
#include <functional>


namespace di::Details {

template<class TYPE> struct FactoryTag { using type = TYPE; };
template<class TYPE> struct SingletonTag { using type = TYPE; };

} // namespace di::Details {
