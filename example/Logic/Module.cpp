#include "Module.h"

#include "Model/Fwd.h"

#include "Impl/Car.h"
#include "Impl/RegularBreak.h"
#include "Impl/ParkingBreak.h"


di::context Logic::moduleContext()
{
    di::context ctx;

    ctx.registerTag<CarTag, Car>();
    ctx.registerTag<RegularBreakTag, RegularBreak>();
    ctx.registerTag<ParkingBreakTag, ParkingBreak>();

    return ctx;
}
