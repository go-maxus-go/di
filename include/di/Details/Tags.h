#pragma once

#include <memory>


namespace di::Details {

struct BaseTag
{
    BaseTag() = delete;
};

template<class T>
struct FactoryTag : BaseTag
{
    using reference = T;
    using pointer = std::unique_ptr<T>;
};

template<class T>
struct SingletonTag : BaseTag
{
    using reference = T;
    using pointer = std::shared_ptr<T>;
};

} // namespace di::Details
