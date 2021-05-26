#pragma once

#include "Gas/Fwd.h"
#include "Brake/Fwd.h"

#include "Car/ICar.h"


namespace Car {

class Ferrari : public ICar
{
public:
    using di = std::tuple<
        Gas::EngineTag,
        Brake::RegularBrakeTag,
        Brake::ParkingBrakeTag>;
    Ferrari(Gas::EnginePtr, Brake::BrakePtr, Brake::BrakePtr);

public: // ICar
    void drive() override;
    void stop() override;

private:
    Gas::EnginePtr m_engine;
    Brake::BrakePtr m_regularBrake;
    Brake::BrakePtr m_parkingBrake;
};

} // namespace Car
