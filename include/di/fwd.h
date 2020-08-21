#pragma once


namespace di {

#define DECLARE_DI_TAG(TagName, InterfaceType) \
    struct TagName { \
        using type = InterfaceType; \
    }

class context;

} // namespace di
