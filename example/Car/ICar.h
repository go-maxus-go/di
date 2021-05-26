#pragma once


namespace Car {

struct ICar
{
    virtual ~ICar() = default;

    virtual void drive() = 0;
    virtual void stop() = 0;
};

} // namespace Car
