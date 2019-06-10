#include "Module.h"

#include <di/context.h>

#include "Model/Fwd.h"

#include "Impl/Car.h"
#include "Impl/RegularBreak.h"
#include "Impl/ParkingBreak.h"


void Logic::registerModule(di::Context & ctx)
{
    ctx.registerTag<CarTag>([&ctx] {
        return std::make_shared<Car>(
                    ctx.resolve<Model::EngineTag>(),
                    ctx.resolve<RegularBreakTag>(),
                    ctx.resolve<ParkingBreakTag>() );
    });

    ctx.registerTag<RegularBreakTag>([&ctx] {
        return std::make_shared<RegularBreak>(
                    ctx.resolve<Model::EngineTag>() );
    });

    ctx.registerTag<ParkingBreakTag>([&ctx] {
        return std::make_shared<ParkingBreak>(
                    ctx.resolve<Model::EngineTag>() );
    });
}
