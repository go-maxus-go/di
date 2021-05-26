#pragma once

#include <memory>

#include <di/fwd.h>


namespace Gas {

struct IEngine;
using EnginePtr = std::shared_ptr<IEngine>;
struct EngineTag : di::singleton_tag<IEngine> {};

} // namespace Gas
