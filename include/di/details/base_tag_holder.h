#pragma once

#include <any>


namespace di::details {

class BaseTagHolder
{
public:
    virtual ~BaseTagHolder() = default;
    virtual bool isResolved() const = 0;
    virtual std::any resolve() const = 0;
};

} // namespace di::details
