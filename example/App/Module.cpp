#include "Module.h"

#include "Logic/Module.h"

#include "Impl/Application.h"


namespace App {

di::context moduleContext()
{
    di::context ctx;

    ctx += Logic::moduleContext();

    ctx.registerTag<ApplicationTag, Application>();

    return ctx;
}

} // namespace App
