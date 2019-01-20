# di
The simplest **C++14** runtime dependency injection library.
## Purpose
The **di** was developed for the sake of practice. The main goal is to keep classes declarations separate from their definitions to reduce compilation time.

In order to approach benefits use only `<di/fwd.h>` in your header files and use `<di/context.h>` in your source files.


## The simplest example
```cpp
#include <di/context.h>

// Declare an interface
struct Interface
{
    virtual ~Interface() = default;
    virtual int method() = 0;
};

// Implement the interface
class Implementation : public Interface
{
public:
    int method() override { return 42; }
};

// Declare lightweight tag for the interface
DECLARE_DI_TAG(InterfaceTag, Interface);

int main()
{
    // Create context
    auto ctx = std::make_shared<di::Context>();

    // Register tags
    ctx->registerTag<InterfaceTag>([]{ return std::make_shared<Implementation>(); });

    // Resolve tags
    auto impl = ctx->resolve<InterfaceTag>();

    // Profit
    assert(impl->method() == 42);

    // Don't forget to clear the context to avoid memory leaks
    ctx->clear();
}
```

## Full project example
You can find more detailed example at the **example** folder. Also you can build it with:

```
cmake example && make
```
