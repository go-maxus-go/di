#pragma once

#include <memory>
#include <functional>


namespace di::Details {

class Context;

template<class Tag> using Type = typename Tag::type;
template<class Tag> using Pointer = typename Tag::pointer;
template<class Tag> using Creator = std::function<Pointer<Tag>(const Context&)>;

class BaseHolder;
using BaseHolderPtr = std::unique_ptr<BaseHolder>;

} // namespace di::Details
