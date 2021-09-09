# What's the DI?
DI is a lightweight header-only runtime [dependency injection](https://en.wikipedia.org/wiki/Dependency_injection) library for C++17.

## Purpose
The main goal of DI is to provide a way of managing dependencies with minimum affordance.
The second important goal is to separate abstract classes from their implementations.
The last but not the least goal is to minimize the effect on the compilation time.

## Example
```cpp
#include <di/context.h>

struct Interface
{
    virtual ~Interface() = default;
};

class Implementation : public Interface {};

// Bind the interface to a lightweight tag.
DECLARE_DI_TAG(InterfaceTag, Interface);

int main()
{
    // Create the context
    auto ctx = di::Context();

    // Register the tag
    ctx.put<InterfaceTag, Implementation>();

    // Resolve the tag
    auto object = ctx.resolve<InterfaceTag>();
}
```

## Full project example
You can find more detailed example in the **example** folder. Also you can build and run it by using:

```
cd example && cmake . && make && ./example
```
// TODO:
Figure out whether unique_ptrs work with singleton
Check test cases
Extend README
Fix example
