# di
The simplest **C++17** runtime dependency injection library.

## Purpose
The main goal of **di** is to keep classes declarations separate from their definitions in order to reduce compilation time.

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
    ctx.registerTag<InterfaceTag, Implementation>();

    // Resolve the tag
    auto object = ctx.resolve<InterfaceTag>();
}
```

## Full project example
You can find more detailed example in the **example** folder. Also you can build and run it by using:

```
cd example && cmake . && make && ./example
```
