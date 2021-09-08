#pragma once

#include <stdexcept>


namespace di::Details {

struct Error : std::logic_error
{
    using std::logic_error::logic_error;
};

} // namespace di::Details
