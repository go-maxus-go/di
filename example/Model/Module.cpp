#include "Module.h"

#include "Impl/Engine.h"


namespace Model {

di::context moduleContext()
{
    di::context ctx;
    ctx.registerTag<EngineTag, Engine>();
    return ctx;
}

} // namespace Model
