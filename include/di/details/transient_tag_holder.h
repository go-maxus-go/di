#pragma once

#include <exception>

#include "fwd.h"
#include "base_tag_holder.h"


namespace di::details {

template<class TAG>
class TransientTagHolder : public BaseTagHolder
{
public:
    TransientTagHolder(Creator<TAG> creator)
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
        return object;
    }

private:
    auto createObject(const Context& context) const
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