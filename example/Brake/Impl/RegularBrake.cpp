#include "RegularBrake.h"

#include <iostream>

#include "Gas/IEngine.h"


namespace Brake {

RegularBrake::RegularBrake(Gas::EnginePtr engine)
    : m_engine(std::move(engine))
{}

void RegularBrake::use(bool use)
{
    std::cout << "Regular brake: " << use << std::endl;
    if (use)
        m_engine->setSpeed(0);
}

} // namespace Brake
