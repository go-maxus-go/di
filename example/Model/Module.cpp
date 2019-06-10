#include "Module.h"

#include <di/context.h>

#include "Impl/Engine.h"


namespace Model {

void registerModule(di::Context & ctx)
{
    ctx.registerTag<EngineTag>([]{ return std::make_shared<Engine>(); });
}

} // namespace Model
