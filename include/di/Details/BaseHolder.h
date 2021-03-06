#pragma once

#include <any>


namespace di {

class context;

namespace Details {

class BaseHolder
{
public:
    virtual ~BaseHolder() = default;
    virtual bool isResolved() const = 0;
    virtual std::any resolve(const context&) const = 0;
};

} // namespace di
} // namespace details
