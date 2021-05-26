#pragma once

#include <memory>

#include <di/fwd.h>


namespace Util {

struct ILogger;
using LoggerPtr = std::shared_ptr<ILogger>;
struct LoggerTag : di::singleton_tag<ILogger> {};

} // namespace Util
