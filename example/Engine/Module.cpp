#include "Module.h"

#include "Impl/Engine.h"


namespace Engine {

di::context moduleContext()
{
    di::context ctx;
    ctx.put<EngineTag, Engine>();
    return ctx;
}

} // namespace Engine
