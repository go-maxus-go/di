#include "Car.h"

#include <iostream>

#include "Model/IEngine.h"

#include "Logic/IBreak.h"


namespace Logic {


Car::Car(Model::EnginePtr engine, BreakPtr regularBreak, BreakPtr parkingBreak)
    : m_engine(std::move(engine))
    , m_regularBreak(std::move(regularBreak))
    , m_parkingBreak(std::move(parkingBreak))
{}

void Car::drive()
{
    std::cout << "Start drive" << std::endl;
    m_engine->setSpeed(100);
}

void Car::useBreak(bool use)
{
    m_regularBreak->use(use);
}

void Car::useParkingBreak(bool use)
{
    m_parkingBreak->use(use);
}

} // namespace Logic
