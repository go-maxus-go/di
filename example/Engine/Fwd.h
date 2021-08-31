#pragma once

#include <memory>

#include <di/di.h>


namespace Engine {

struct IEngine;
using EnginePtr = std::shared_ptr<IEngine>;
struct EngineTag : di::singleton_tag<IEngine> {};

} // namespace Engine
