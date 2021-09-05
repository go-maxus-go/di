#pragma once

#include <memory>
#include <functional>


namespace di::Details {

struct BaseTag
{
    BaseTag() = delete;
};

template<class TYPE>
struct FactoryTag : BaseTag
{
    using type = TYPE;
};

template<class TYPE>
struct SingletonTag : BaseTag
{
    using type = TYPE;
};

} // namespace di::Details {
