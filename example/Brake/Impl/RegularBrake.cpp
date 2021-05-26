#include "RegularBrake.h"

#include <iostream>

#include "Engine/IEngine.h"


namespace Brake {

RegularBrake::RegularBrake(Engine::EnginePtr engine)
    : m_engine(std::move(engine))
{}

void RegularBrake::use(bool use)
{
    std::cout << "Regular brake: " << use << std::endl;
    if (use)
        m_engine->setSpeed(0);
}

} // namespace Brake
