#include "ClientModule.h"

#include "ClientTags.h"

#include "Client.h"


di::context Client::createClientContext()
{
    di::context ctx;

    ctx.put<ClientTag>();

    return ctx;
}
