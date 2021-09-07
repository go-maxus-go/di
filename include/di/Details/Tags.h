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
    using type = T;
    using pointer = std::unique_ptr<T>;
};

template<class T>
struct SingletonTag : BaseTag
{
    using type = T;
    using pointer = std::shared_ptr<T>;
};


// TODO: move out of here
template<class IMPL, class T>
constexpr std::unique_ptr<IMPL>* ImplPointer(FactoryTag<T>*);

template<class IMPL, class T>
constexpr std::shared_ptr<IMPL>* ImplPointer(SingletonTag<T>*);

} // namespace di::Details
