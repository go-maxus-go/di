#pragma once

#include <exception>

#include "fwd.h"
#include "base_tag_holder.h"


namespace di::details {

template<class TAG>
class SingletonTagHolder : public BaseTagHolder
{
public:
    SingletonTagHolder(Creator<TAG> creator)
        : creator(std::move(creator))
    {}

    bool isResolved() const override
    {
        return result != nullptr;
    }

    std::any resolve() const override
    {
        if (result != nullptr)
            return result;
        result = createObject();
        return result;
    }

private:
    auto createObject() const
    {
        auto object = creator();
        if (object == nullptr)
            throw std::logic_error("di: creator produces null pointer object");
        return object;
    }

private:
    Creator<TAG> creator;
    mutable ObjectPtr<TAG> result;
};

} // namespace di::details
