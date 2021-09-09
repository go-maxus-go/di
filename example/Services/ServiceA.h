#pragma once

#include <iostream>

#include "IServiceA.h"


namespace Services {

class ServiceA : public IServiceA
{
public:
    void useServiceA() const override
    {
        std::cout << "Service A is used" << std::endl;
    }
};

} // namespace Services
