#pragma once

#include <memory>

#include <di/fwd.h>


namespace Logic {

struct ICar;
using CarPtr = std::shared_ptr<ICar>;
struct CarTag : di::singleton_tag<ICar> {};

struct IBreak;
using BreakPtr = std::shared_ptr<IBreak>;
struct RegularBreakTag : di::singleton_tag<IBreak> {};
struct ParkingBreakTag : di::singleton_tag<IBreak> {};

} // namespace Logic
