#pragma once

#include <memory>


namespace di {

#define DECLARE_DI_TAG(TagName, InterfaceType) \
    struct TagName { \
        using type = InterfaceType; \
    };

class Context;

} // namespace di
