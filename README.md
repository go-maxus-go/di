# What's the DI?
DI is a lightweight header-only runtime [dependency injection](https://en.wikipedia.org/wiki/Dependency_injection) library for C++17.

## Purpose
The main goal of DI is to provide a way of managing dependencies with minimum affordance.
The second important goal is to separate abstract classes from their implementations.
The last but not the least goal is to minimize the effect on the compilation time.

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
In **example** folder you can find an implementation of [Client/Services](https://en.wikipedia.org/wiki/Dependency_injection#Roles) example from wiki. The example can build it with CMake.
```
cd example
cmake .
make
```
