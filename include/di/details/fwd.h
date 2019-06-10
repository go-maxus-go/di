#pragma once

#include <memory>
#include <functional>


namespace di {
namespace details {

template<class TAG> using Type = typename TAG::type;
template<class TAG> using ObjectPtr = std::shared_ptr<Type<TAG>>;
template<class TAG> using Creator = std::function<ObjectPtr<TAG>()>;

class BaseTagHolder;
using BaseHolderPtr = std::unique_ptr<BaseTagHolder>;

} // namespace di
} // namespace details
