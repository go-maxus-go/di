#include <di/di.h>

#include "App/Module.h"
#include "App/IApplication.h"


int main()
{
    auto ctx = App::moduleContext();

    auto app = ctx.resolve<App::ApplicationTag>();

    return app->exec();
}
