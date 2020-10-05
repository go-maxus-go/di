#pragma once

#include <exception>

#include "Fwd.h"
#include "BaseHolder.h"


namespace di::Details {

template<class CREATOR>
class FactoryHolder : public BaseHolder
{
public:
    FactoryHolder(CREATOR creator)
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
    CREATOR creator;
    mutable bool resolved = false;
};

} // namespace di::details
