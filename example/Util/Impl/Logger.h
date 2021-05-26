#pragma once

#include <memory>

#include "Util/ILogger.h"


namespace Util {

class Logger : public ILogger
{
public: // ILogger
    void info(const std::string& str) const override;
};

} // namespace Util
