#pragma once

#include <any>


namespace di {

class Context;

namespace details {

class BaseTagHolder
{
public:
    virtual ~BaseTagHolder() = default;
    virtual bool isResolved() const = 0;
    virtual std::any resolve(const Context&) const = 0;
};

} // namespace di
} // namespace details
