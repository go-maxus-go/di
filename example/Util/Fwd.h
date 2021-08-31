#pragma once

#include <memory>

#include <di/di.h>


namespace Util {

struct ILogger;
using LoggerPtr = std::shared_ptr<ILogger>;
struct LoggerTag : di::singleton_tag<ILogger> {};

} // namespace Util
