#pragma once


namespace di {

namespace Details {

class Context;

template<class T>
class FactoryTag;

template<class T>
class SingletonTag;

} // namespace Details

/*
 * Holds and resolves dependencies.
*/
using context = Details::Context;

/*
 * Is used for creating a new instance of a class on each call.
*/
template<class T>
using factory_tag = Details::FactoryTag<T>;

/*
 * Is used for creating the only one instance of a class.
 * The instance will be cached and returned on each call.
*/
template<class T>
using singleton_tag = Details::SingletonTag<T>;

} // namespace di
