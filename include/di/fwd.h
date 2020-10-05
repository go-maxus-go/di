#pragma once

#include "Details/Fwd.h"


namespace di {

#define DECLARE_DI_TAG(TagName, InterfaceType) \
    struct TagName : ::di::tag<InterfaceType> {}

class context;

template<class InterfaceType>
using tag = Details::Tag<InterfaceType>;

} // namespace di
