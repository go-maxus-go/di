#pragma once

#include <tuple>
#include <memory>

#include "Services/IServiceA.h"
#include "Services/IServiceB.h"

#include "Services/ServicesTags.h"


namespace Client {

class Client
{
public:
    using di_deps = std::tuple<Services::ServiceATag, Services::ServiceBTag>;
    Client(
        std::shared_ptr<Services::IServiceA> serviceA,
        std::shared_ptr<Services::IServiceB> serviceB)
        : serviceA{std::move(serviceA)}
        , serviceB{std::move(serviceB)}
    {}

    void useServiceA() const
    {
        serviceA->useServiceA();
    }

    void useServiceB() const
    {
        serviceB->useServiceB();
    }

private:
    std::shared_ptr<Services::IServiceA> serviceA;
    std::shared_ptr<Services::IServiceB> serviceB;
};

} // namespace Client
