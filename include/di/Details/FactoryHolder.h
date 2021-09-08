#pragma once

#include "Fwd.h"
#include "Error.h"
#include "BaseHolder.h"


namespace di::Details {

template<class TAG>
class FactoryHolder : public BaseHolder
{
public:
    FactoryHolder(Creator<TAG> creator)
        : creator(std::move(creator))
    {}

    bool isResolved() const override
    {
        return resolved;
    }

    std::any resolve(const Context& context) const override
    {
        auto object = createObject(context);
        setResolved();
        return object.release();
    }

private:
    auto createObject(const Context& context) const
    {
        auto object = creator(context);
        if (object == nullptr)
            throw Error("di: creator produces null pointer object");
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
