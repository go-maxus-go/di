#include "Logger.h"

#include <iostream>


namespace Util {

void Logger::info(const std::string& str) const
{
    std::cout << "Info: " << str << std::endl;
}

} // namespace Util
