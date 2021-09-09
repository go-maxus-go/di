#pragma once

#include <iostream>

#include "IServiceB.h"


namespace Services {

class ServiceB : public IServiceB
{
public:
    void useServiceB() const override
    {
        std::cout << "Service B is used" << std::endl;
    }
};

} // namespace Services
