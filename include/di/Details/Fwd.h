#pragma once

#include <memory>
#include <functional>


namespace di::Details {

class Context;

template<class TAG> using Type = typename TAG::type;
template<class TAG> using Pointer = typename TAG::pointer;
template<class TAG> using Creator = std::function<Pointer<TAG>(const Context&)>;

class BaseHolder;
using BaseHolderPtr = std::unique_ptr<BaseHolder>;

} // namespace di::Details
