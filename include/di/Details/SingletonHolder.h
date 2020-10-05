#pragma once

#include <exception>

#include "Fwd.h"
#include "BaseHolder.h"


namespace di::Details {

template<class CREATOR>
class SingletonHolder : public BaseHolder
{
public:
    SingletonHolder(CREATOR creator)
        : creator(std::move(creator))
    {}

    bool isResolved() const override
    {
        return result != nullptr;
    }

    std::any resolve(const context& context) const override
    {
        if (result != nullptr)
            return result;
        result = createObject(context);
        return result;
    }

private:
    auto createObject(const context& context) const
    {
        auto object = creator(context);
        if (object == nullptr)
            throw std::logic_error("di: creator produces null pointer object");
        return object;
    }

private:
    CREATOR creator;
    mutable typename std::invoke_result<CREATOR, context>::type result;
};

} // namespace di::details
