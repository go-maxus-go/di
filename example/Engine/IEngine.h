#pragma once


namespace Engine {

struct IEngine
{
    virtual ~IEngine() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void setSpeed(int speed) = 0;
};

} // namespace Engine
