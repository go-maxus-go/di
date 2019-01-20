#pragma once


namespace Logic {

struct ICar
{
    virtual ~ICar() = default;

    virtual void drive() = 0;
    virtual void useBreak(bool) = 0;
    virtual void useParkingBreak(bool) = 0;
};

} // namespace Logic
