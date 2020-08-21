#include <di/context.h>

#include "Model/Module.h"
#include "Logic/Module.h"

#include "Logic/ICar.h"


int main()
{
    auto ctx = di::context();

    ctx += Model::moduleContext();
    ctx += Logic::moduleContext();

    auto car = ctx.resolve<Logic::CarTag>();

    car->useParkingBreak(false);
    car->drive();
    car->useBreak(true);
    car->useParkingBreak(true);
}
