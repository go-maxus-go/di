#define CATCH_CONFIG_MAIN
#include <catch.hpp>


// context behavior tests. context destruction, context moving, context merging,
// context tag registration after resolve is called.

// Object tests. object tag registration and dependencies resolving.
// Interface tests. Interface tag registration and dependencies resolving.

// Factory tag tests.
// Singleton tag tests.

// Custom creator tests.
// di_deps single dependency tests.
// di_deps dependency list as a tuple tests.

// Can I put di_deps into a tag? Yes, I can.

// Test each case with minimum amount of objects.
// For simple di_deps use 1 object, for di_deps with tuple use 2 objects
