#pragma once

#include "Brake/IBrake.h"


namespace Brake {

class ParkingBrake : public IBrake
{
public: // IBrake
    void use(bool use) override;
};

} // namespace Brake
