#pragma once

#include <di/tags.h>


namespace Client {

class Client;
struct ClientTag : di::factory_tag<Client> {};

} // namespace Client
