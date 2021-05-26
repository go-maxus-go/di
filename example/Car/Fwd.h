#pragma once

#include <memory>

#include <di/fwd.h>


namespace Car {

struct ICar;
using CarPtr = std::shared_ptr<ICar>;
struct CarTag : di::singleton_tag<ICar> {};

} // namespace Car
