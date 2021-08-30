#pragma once

#include "Details/Tags.h"
#include "Details/Context.h"


namespace di {

/*
 * The class containing all dependencies.
*/
using context = Details::Context;

/*
 * This tag is used for creating a new instance of a class on each call.
*/
template<class T>
using factory_tag = Details::FactoryTag<T>;

/*
 * This tag is used for creating the only one instance of a class.
 * The instance will be cached and returned on each call.
*/
template<class T>
using singleton_tag = Details::SingletonTag<T>;

} // namespace di
