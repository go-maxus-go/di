#pragma once

#include "Gas/Fwd.h"

#include "Brake/IBrake.h"


namespace Brake {

class RegularBrake : public IBrake
{
public:
    using di = Gas::EngineTag;
    RegularBrake(Gas::EnginePtr);

public: // IBrake
    void use(bool use) override;

private:
    Gas::EnginePtr m_engine;
};

} // namespace Brake
