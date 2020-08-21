#pragma once

#include <memory>

#include <di/fwd.h>


namespace Logic {

struct ICar;
using CarPtr = std::shared_ptr<ICar>;

struct IBreak;
using BreakPtr = std::shared_ptr<IBreak>;

DECLARE_DI_TAG(CarTag, ICar);
DECLARE_DI_TAG(RegularBreakTag, IBreak);
DECLARE_DI_TAG(ParkingBreakTag, IBreak);

} // namespace Logic
