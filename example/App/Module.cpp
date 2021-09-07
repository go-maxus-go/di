#include "Module.h"

#include "Car/Module.h"

#include "Impl/Application.h"


namespace App {

di::context moduleContext()
{
    di::context ctx;

    ctx += Car::moduleContext();

    ctx.put<ApplicationTag, Application>();

    return ctx;
}

} // namespace App
