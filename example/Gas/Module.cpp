#include "Module.h"

#include "Impl/Engine.h"


namespace Gas {

di::context moduleContext()
{
    di::context ctx;
    ctx.registerTag<EngineTag, Engine>();
    return ctx;
}

} // namespace Gas
