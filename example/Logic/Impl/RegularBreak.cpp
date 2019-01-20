#include "RegularBreak.h"

#include <iostream>

#include "Model/IEngine.h"


namespace Logic {

RegularBreak::RegularBreak(Model::EnginePtr engine)
    : m_engine(std::move(engine))
{}

void RegularBreak::use(bool use)
{
    std::cout << "Regular break: " << use << std::endl;
    if (use)
        m_engine->setSpeed(0);
}

} // namespace Logic
