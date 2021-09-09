#include <di/context.h>

#include "Client/Client.h"
#include "Client/ClientTags.h"
#include "Client/ClientModule.h"

#include "Services/ServicesModule.h"


int main()
{
    di::context ctx;
    ctx += Client::createClientContext();
    ctx += Services::createServicesContext();

    const auto client = ctx.resolve<Client::ClientTag>();
    client->useServiceA();
    client->useServiceB();

    return 0;
}
