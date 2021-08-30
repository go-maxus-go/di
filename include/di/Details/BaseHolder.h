#pragma once

#include <any>


namespace di::Details {

class Context;

class BaseHolder
{
public:
    virtual ~BaseHolder() = default;
    virtual bool isResolved() const = 0;
    virtual std::any resolve(const Context&) const = 0;
};

} // namespace di::Details
