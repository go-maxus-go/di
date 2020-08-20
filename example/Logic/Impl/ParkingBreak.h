#pragma once

#include <memory>

#include "Model/Fwd.h"

#include "Logic/IBreak.h"


namespace Logic {

class ParkingBreak : public IBreak
{
public:
    using di = std::tuple<Model::EngineTag>;
    ParkingBreak(Model::EnginePtr);

public: // IBreak
    void use(bool use) override;

private:
    Model::EnginePtr m_engine;
};

} // namespace Logic
