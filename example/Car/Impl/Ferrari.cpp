#include "Ferrari.h"

#include "Gas/IEngine.h"

#include "Brake/IBrake.h"


namespace Car {


Ferrari::Ferrari(Gas::EnginePtr engine, Brake::BrakePtr regularBrake, Brake::BrakePtr parkingBrake)
    : m_engine(std::move(engine))
    , m_regularBrake(std::move(regularBrake))
    , m_parkingBrake(std::move(parkingBrake))
{}

void Ferrari::drive()
{
    m_engine->start();
    m_parkingBrake->use(false);
    m_regularBrake->use(false);
    m_engine->setSpeed(100);
}

void Ferrari::stop()
{
    m_regularBrake->use(true);
    m_parkingBrake->use(true);
    m_engine->stop();
}

} // namespace Car
