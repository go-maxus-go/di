#include "Module.h"

#include "Gas/Module.h"
#include "Brake/Module.h"

#include "Impl/Ferrari.h"


di::context Car::moduleContext()
{
    di::context ctx;

    ctx += Gas::moduleContext();
    ctx += Brake::moduleContext();

    ctx.registerTag<CarTag, Ferrari>();

    return ctx;
}
