#include "ParkingBreak.h"

#include <iostream>

#include "Model/IEngine.h"


namespace Logic {

ParkingBreak::ParkingBreak(Model::EnginePtr engine)
    : m_engine(std::move(engine))
{}

void ParkingBreak::use(bool use)
{
    std::cout << "Parking break: " << use << std::endl;
    if (use)
        m_engine->setSpeed(0);
}

} // namespace Logic
