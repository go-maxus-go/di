#include "Common.h"


namespace {

const auto testArg = "[CustomCreatorTest]";

struct Foo {
    using di = std::tuple<>;
};
using FooPtr = Ptr<Foo>;
DECLARE_DI_TAG(FooTag, Foo);

struct Bar {
    using di = std::tuple<FooTag>;
    Bar(FooPtr foo)
        : foo(std::move(foo))
    {}
    FooPtr foo;
};
using BarPtr = Ptr<Bar>;
DECLARE_DI_TAG(BarTag, Bar);

struct Baz {};
using BazPtr = Ptr<Baz>;
DECLARE_DI_TAG(BazTag, Baz);

di::context createContext()
{
    auto ctx = di::context();

    ctx.registerTag<FooTag>([](const auto &) {
        return std::make_shared<Foo>();
    });
    ctx.registerTag<BarTag>([](const di::context & ctx) {
        return std::make_shared<Bar>(ctx.resolve<FooTag>());
    });
    ctx.registerFactoryTag<BazTag>([](const auto &) {
        return std::make_shared<Baz>();
    });

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

TEST_CASE("Context destruction releases objects", testArg)
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

TEST_CASE("Factory tag registering and resolving ", testArg)
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
