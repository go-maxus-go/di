#pragma once


namespace Model {

struct IEngine
{
    virtual ~IEngine() = default;

    virtual int speed() const = 0;
    virtual void setSpeed(int) = 0;
};

} // namespace Model
