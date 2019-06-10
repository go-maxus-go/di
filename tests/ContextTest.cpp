#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <di/context.h>


namespace {

const auto testArg = "[LevelBackground]";

template<class T> using Ptr = std::shared_ptr<T>;

struct Foo {};
using FooPtr = Ptr<Foo>;
DECLARE_DI_TAG(FooTag, Foo);

struct Bar {
    Bar(FooPtr foo) : foo(std::move(foo)) {}
    FooPtr foo;
};
using BarPtr = Ptr<Bar>;
DECLARE_DI_TAG(BarTag, Bar);

struct Baz {};
using BazPtr = Ptr<Baz>;
DECLARE_DI_TAG(BazTag, Baz);

auto createContext()
{
    auto ctx = di::Context();
    ctx.registerTag<FooTag>([]{ return std::make_shared<Foo>(); });
    ctx.registerTag<BarTag>([ctx]{ return std::make_shared<Bar>(ctx.resolve<FooTag>()); });
    ctx.registerTransientTag<BazTag>([]{ return std::make_shared<Baz>(); });
    return ctx;
}

} // anonymous namespace

TEST_CASE("Register tag and resolve it", testArg)
{
    auto ctx = createContext();

    const auto foo = ctx.resolve<FooTag>();

    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Register tag and resolve it several times", testArg)
{
    auto ctx = createContext();

    const auto foo1 = ctx.resolve<FooTag>();
    const auto foo2 = ctx.resolve<FooTag>();

    REQUIRE(foo1 == foo2);
}

TEST_CASE("Register a couple of tag and resolve it", testArg)
{
    auto ctx = createContext();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
    REQUIRE(typeid(*bar) == typeid(Bar));

    const auto foo = bar->foo;
    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Context destructor releases objects", testArg)
{
    std::weak_ptr<Foo> weakPtr;
    {
        auto ctx = createContext();

        const auto foo = ctx.resolve<FooTag>();
        weakPtr = std::weak_ptr<Foo>(foo);

        REQUIRE(weakPtr.lock() != nullptr);
    }
    REQUIRE(weakPtr.lock() == nullptr);
}

TEST_CASE("Transient tag registering and resolving ", testArg)
{
    auto ctx = createContext();

    const auto baz1 = ctx.resolve<BazTag>();
    const auto baz2 = ctx.resolve<BazTag>();

    REQUIRE(baz1 != baz2);

    REQUIRE(baz1 != nullptr);
    REQUIRE(typeid(*baz1) == typeid(Baz));

    REQUIRE(baz2 != nullptr);
    REQUIRE(typeid(*baz2) == typeid(Baz));
}
