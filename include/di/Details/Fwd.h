#pragma once

#include <memory>
#include <functional>


namespace di {

class context;

namespace Details {

template<class T> struct Tag { using type = T; };

template<class TAG> using Type = typename TAG::type;
template<class TYPE> using Pointer = std::shared_ptr<TYPE>;
template<class TAG> using ObjectPtr = Pointer<Type<TAG>>;
template<class TAG> using CreatorByTag = std::function<ObjectPtr<TAG>(const context&)>;
template<class TYPE> using CreatorByType = std::function<Pointer<TYPE>(const context&)>;

class BaseHolder;
using BaseHolderPtr = std::unique_ptr<BaseHolder>;

} // namespace di
} // namespace details
