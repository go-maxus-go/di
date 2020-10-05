#include "Common.h"


namespace {

const auto testArg = "[InterfaceResolveTest]";

struct IFoo
{
    virtual ~IFoo() = default;
    virtual int id() const = 0;
};
using FooPtr = Ptr<IFoo>;
DECLARE_DI_TAG(FooTag, IFoo);

struct FooImpl : IFoo
{
    int id() const override { return 42; }
};

struct IBar
{
    virtual ~IBar() = default;
    virtual int id() const = 0;
};
using BarPtr = Ptr<IBar>;
DECLARE_DI_TAG(BarTag, IBar);

struct BarImpl : IBar
{
    using di = std::tuple<FooTag>;
    BarImpl(FooPtr foo) : foo(std::move(foo))
    {}
    int id() const override { return foo->id() * 10; }

    FooPtr foo;
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

TEST_CASE("Register and resolve an interface", testArg)
{
    auto ctx = di::context();
    //ctx.registerType<IFoo>([](const auto&){ return std::make_shared<FooImpl>(); });
    ctx.registerTag<FooTag, FooImpl>();
    ctx.registerType<IBar, BarImpl>();

    auto bar = ctx.resolve<IBar>();
    REQUIRE(bar != nullptr);
    REQUIRE(bar->id() == 420);
}
