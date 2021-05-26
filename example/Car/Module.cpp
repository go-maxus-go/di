#include "Module.h"

#include "Engine/Module.h"
#include "Brake/Module.h"

#include "Impl/Ferrari.h"


di::context Car::moduleContext()
{
    di::context ctx;

    ctx += Engine::moduleContext();
    ctx += Brake::moduleContext();

    ctx.registerTag<CarTag, Ferrari>();

    return ctx;
}
