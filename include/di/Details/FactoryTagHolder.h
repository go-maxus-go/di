#pragma once

#include <exception>

#include "Fwd.h"
#include "BaseTagHolder.h"


namespace di::Details {

template<class TAG>
class FactoryTagHolder : public BaseTagHolder
{
public:
    FactoryTagHolder(Creator<TAG> creator)
        : creator(std::move(creator))
    {}

    bool isResolved() const override
    {
        return resolved;
    }

    std::any resolve(const context& context) const override
    {
        auto object = createObject(context);
        setResolved();
        return object;
    }

private:
    auto createObject(const context& context) const
    {
        auto object = creator(context);
        if (object == nullptr)
            throw std::logic_error("di: creator produces null pointer object");
        return object;
    }

    void setResolved() const
    {
        resolved = true;
    }

private:
    Creator<TAG> creator;
    mutable bool resolved = false;
};

} // namespace di::details
