#include "Common.h"


namespace {

const auto testArg = "[InterfaceResolveTest]";

struct IFoo
{
    virtual ~IFoo() = default;
    virtual int id() const = 0;
};
struct FooTag : di::singleton_tag<IFoo> {};

struct FooImpl : IFoo
{
    int id() const override { return 42; }
};

struct IBar
{
    virtual ~IBar() = default;
    virtual int id() const = 0;
};
struct BarTag : di::factory_tag<IBar> {};

struct BarImpl : IBar
{
    using di = std::tuple<FooTag>;
    BarImpl(std::shared_ptr<IFoo> foo)
        : foo(std::move(foo))
    {}

    int id() const override { return foo->id() * 10; }

    std::shared_ptr<IFoo> foo;
};

} // anonymous namespace

TEST_CASE("Register and resolve a single tag", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<FooTag, FooImpl>();

    auto foo = ctx.resolve<FooTag>();
    REQUIRE(foo != nullptr);
    REQUIRE(foo->id() == 42);
}

TEST_CASE("Register and resolve a dependency", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<FooTag, FooImpl>();
    ctx.registerTag<BarTag, BarImpl>();

    auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
    REQUIRE(bar->id() == 420);
}
