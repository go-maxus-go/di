#pragma once

#include <memory>

#include <di/fwd.h>


namespace App {

struct IApplication;
using ApplicationPtr = std::shared_ptr<IApplication>;
struct ApplicationTag : di::singleton_tag<IApplication> {};

} // namespace App
