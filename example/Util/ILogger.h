#pragma once


namespace Util {

struct ILogger
{
    virtual ~ILogger() = default;
    virtual void info(const std::string& str) const = 0;
};

} // namespace Model
