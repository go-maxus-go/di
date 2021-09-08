#pragma once


namespace di::Details {

template<class T>
struct TypeIdentity {
    using type = T;
};

template<class T>
using Ti = TypeIdentity<T>;

} // namespace di::Details
