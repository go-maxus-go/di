## What's the DI?
DI is a lightweight header-only runtime [dependency injection](https://en.wikipedia.org/wiki/Dependency_injection) library compatible with C++17.

## Purpose
The main goal of DI is to provide a way of managing dependencies with minimum affordance.
The second important goal is to separate abstract classes from their implementations.
The last but not the least goal is to minimize the effect on the compilation time.

## How does DI work?
DI provides a class ```di::context``` also it might be better known as "injector".
Also DI provides ```di::singleton_tag``` and ```di::factory_tag```.
Tag are a lightweight structures with a reference to the result type.
The dependencies management is performed by the context based on provided tags.

## Hello world
In this small example a concrete class ```Foo``` will be built by ```di::context```.
As the first step, a singleton tag ```FooTag``` should be defined.
```cpp
#include <di/tags.h>

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};
```
As the second step, the tag should be added to the context.
```cpp
#include <di/context.h>

di::context ctx;
ctx.put<FooTag>();
```
As the final step, the context builds an instance of ```Foo```.
The result is provided using shared pointer because ```FooTag``` is based on the singleton tag.
If the context resolve is called multiple times the same result will be returned.
```cpp
std::shared_ptr<Foo> foo = ctx.resolve<FooTag>();
assert(foo == ctx.resolve<FooTag>());
```

## Example
```cpp
#include <memory>
#include <iostream>

#include <di/tags.h>
#include <di/context.h>

struct IFoo {
    virtual ~IFoo() = delete;
    virtual void fun() = 0;
};

struct Foo : IFoo {
    void fun() override {
        std::cout << "Have fun" << std::endl;
    }
};

struct FooTag : di::singleton_tag<IFoo> {};

int main() {
    di::context ctx;
    ctx.put<FooTag, Foo>();

    auto foo = ctx.resolve<FooTag>();
    foo->fun();
}
```

## Client/Services example
In **example** folder you can find an implementation of a very similar [Client/Services  example](https://en.wikipedia.org/wiki/Dependency_injection#Roles) with di::context instead of Injector. The example can build it with CMake.
```
cd example
cmake .
make
```
## Compatible compilers
DI requires C++17 or higher. DI is tested on GCC 8.1, Clang 12.0, MSVC 15.9.
