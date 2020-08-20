#pragma once

#include "Model/Fwd.h"

#include "Logic/Fwd.h"
#include "Logic/ICar.h"


namespace Logic {

class Car : public ICar
{
public:
    using di = std::tuple<Model::EngineTag, RegularBreakTag, ParkingBreakTag>;
    Car(Model::EnginePtr engine, BreakPtr regularBreak, BreakPtr parkingBreak);

public: // ICar
    void drive() override;
    void useBreak(bool use) override;
    void useParkingBreak(bool use) override;

private:
    Model::EnginePtr m_engine;
    BreakPtr m_regularBreak;
    BreakPtr m_parkingBreak;
};

} // namespace Logic
