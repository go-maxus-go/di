#pragma once

#include "Fwd.h"
#include "Error.h"
#include "BaseHolder.h"


namespace di::Details {

template<class TAG>
class SingletonHolder : public BaseHolder
{
public:
    SingletonHolder(Creator<TAG> creator)
        : creator(std::move(creator))
    {}

    bool isResolved() const override
    {
        return result != nullptr;
    }

    std::any resolve(const Context& context) const override
    {
        if (result != nullptr)
            return result;
        result = creator(context);
        if (result == nullptr)
            throw Error("Creator returned null");
        return result;
    }

private:
    Creator<TAG> creator;
    mutable std::shared_ptr<Type<TAG>> result;
};

} // namespace di::details
