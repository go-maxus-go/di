#include "Module.h"

#include "Engine/Module.h"

#include "Impl/RegularBrake.h"
#include "Impl/ParkingBrake.h"


di::context Brake::moduleContext()
{
    di::context ctx;

    ctx += Engine::moduleContext();

    ctx.put<RegularBrakeTag, RegularBrake>();
    ctx.put<ParkingBrakeTag, ParkingBrake>();

    return ctx;
}
