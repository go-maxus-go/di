#pragma once


namespace di {

class context;

template<class TYPE> struct factory_tag { using type = TYPE; };
template<class TYPE> struct singleton_tag { using type = TYPE; };

} // namespace di
