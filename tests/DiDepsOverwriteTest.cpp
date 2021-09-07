#include "Common.h"


namespace {

struct IFoo
{
    virtual ~IFoo() = default;
    virtual int fun() const = 0;
};
struct Foo1 : IFoo
{
    int fun() const override { return 1; }
};
struct Foo1Tag : di::singleton_tag<IFoo> {};

struct Foo2 : IFoo
{
    int fun() const override { return 2; }
};
struct Foo2Tag : di::singleton_tag<IFoo> {};

struct Bar
{
    using di_deps = Foo1Tag;
    Bar(std::shared_ptr<IFoo> foo) : foo(std::move(foo))
    {}
    std::shared_ptr<IFoo> foo;
};
struct BarTag : di::singleton_tag<Bar> {};

TEST_CASE("Custom creator overwrites di_deps from the object")
{
    di::context ctx;
    ctx.put<Foo1Tag, Foo1>();
    ctx.put<Foo2Tag, Foo2>();
    ctx.put<BarTag>([](const di::context& ctx) {
        auto foo = ctx.resolve<Foo2Tag>();
        return std::make_unique<Bar>(std::move(foo));
    });

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar->foo->fun() == 2);
}

TEST_CASE("Dependencies passed to the context overwrite di_deps from the object")
{
    di::context ctx;
    ctx.put<Foo1Tag, Foo1>();
    ctx.put<Foo2Tag, Foo2>();
    ctx.put<BarTag, Foo2Tag>();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar->foo->fun() == 2);
}

} // anonymous namespace
