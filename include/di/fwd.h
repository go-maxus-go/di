#pragma once

#include <memory>


namespace di {

#define DECLARE_DI_TAG(Tag, Type) struct Tag { using type = Type; };

class Context;

} // namespace di
