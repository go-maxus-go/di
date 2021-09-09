#pragma once


namespace Services {

class IServiceA
{
public:
    virtual ~IServiceA() = default;

    virtual void useServiceA() const = 0;
};

} // namespace Services
