#pragma once

#include "Engine/Fwd.h"

#include "Brake/IBrake.h"


namespace Brake {

class RegularBrake : public IBrake
{
public:
    using di = Engine::EngineTag;
    RegularBrake(Engine::EnginePtr);

public: // IBrake
    void use(bool use) override;

private:
    Engine::EnginePtr m_engine;
};

} // namespace Brake
