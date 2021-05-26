#include "Module.h"

#include "Gas/Module.h"

#include "Impl/RegularBrake.h"
#include "Impl/ParkingBrake.h"


di::context Brake::moduleContext()
{
    di::context ctx;

    ctx += Gas::moduleContext();

    ctx.registerTag<RegularBrakeTag, RegularBrake>();
    ctx.registerTag<ParkingBrakeTag, ParkingBrake>();

    return ctx;
}
