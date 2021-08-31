#pragma once

#include <memory>

#include <di/di.h>


namespace Brake {

struct IBrake;
using BrakePtr = std::shared_ptr<IBrake>;
struct RegularBrakeTag : di::singleton_tag<IBrake> {};
struct ParkingBrakeTag : di::singleton_tag<IBrake> {};

} // namespace Brake
