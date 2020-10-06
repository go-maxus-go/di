#pragma once

#include <memory>
#include <functional>


namespace di {

class context;

namespace Details {

template<class TAG> using Type = typename TAG::type;
template<class TYPE> using Pointer = std::unique_ptr<TYPE>;
template<class TAG> using ObjectPtr = Pointer<Type<TAG>>;
template<class TAG> using Creator = std::function<ObjectPtr<TAG>(const context&)>;

class BaseHolder;
using BaseHolderPtr = std::unique_ptr<BaseHolder>;

} // namespace di
} // namespace details
