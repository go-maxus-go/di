#pragma once

#include <memory>

#include <di/fwd.h>


namespace Model {

struct IEngine;
using EnginePtr = std::shared_ptr<IEngine>;

DECLARE_DI_TAG(EngineTag, IEngine);

} // namespace Model
