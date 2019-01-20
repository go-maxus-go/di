#pragma once


namespace Logic {

struct IBreak
{
    virtual ~IBreak() = default;

    virtual void use(bool) = 0;
};

} // namespace Logic
