#include "Module.h"

#include "Impl/Engine.h"


namespace Model {

di::context moduleContext()
{
    di::context ctx;
    ctx.registerTag<EngineTag, Engine>(std::tuple<>());
    return ctx;
}

} // namespace Model
