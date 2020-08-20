#include "Module.h"

#include "Impl/Engine.h"


namespace Model {

di::Context moduleContext()
{
    di::Context ctx;
    ctx.registerTag<EngineTag, Engine>(std::tuple<>());
    return ctx;
}

} // namespace Model
