#include "Module.h"

#include "Impl/Logger.h"


namespace Util {

di::context moduleContext()
{
    di::context ctx;
    ctx.registerTag<LoggerTag, Logger>();
    return ctx;
}

} // namespace Util
