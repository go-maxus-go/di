#pragma once


namespace Services {

class IServiceB
{
public:
    virtual ~IServiceB() = default;

    virtual void useServiceB() const = 0;
};

} // namespace Services
