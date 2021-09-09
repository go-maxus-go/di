#pragma once

#include <di/tags.h>


namespace Services {

class IServiceA;
struct ServiceATag :di::singleton_tag<IServiceA> {};

class IServiceB;
struct ServiceBTag :di::singleton_tag<IServiceB> {};

} // namespace Services
