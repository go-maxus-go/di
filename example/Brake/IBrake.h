#pragma once


namespace Brake {

struct IBrake
{
    virtual ~IBrake() = default;

    virtual void use(bool) = 0;
};

} // namespace Brake
