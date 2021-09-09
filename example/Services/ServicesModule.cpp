#include "ServicesModule.h"

#include "ServicesTags.h"

#include "ServiceA.h"
#include "ServiceB.h"


di::context Services::createServicesContext()
{
    di::context ctx;

    ctx.put<ServiceATag, ServiceA>();
    ctx.put<ServiceBTag, ServiceB>();

    return ctx;
}
