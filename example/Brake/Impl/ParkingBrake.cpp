#include "ParkingBrake.h"

#include <iostream>


namespace Brake {

void ParkingBrake::use(bool use)
{
    std::cout << "Parking brake: " << use << std::endl;
}

} // namespace Brake
