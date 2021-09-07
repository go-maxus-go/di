#include "Module.h"

#include "Impl/Logger.h"


namespace Util {

di::context moduleContext()
{
    di::context ctx;
    ctx.put<LoggerTag, Logger>();
    return ctx;
}

} // namespace Util
