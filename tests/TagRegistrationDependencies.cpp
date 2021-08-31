#include "Common.h"


namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

struct Bar {
    Bar(std::shared_ptr<Foo> foo)
        : foo(std::move(foo))
    {}
    std::shared_ptr<Foo> foo;
};
struct BarTag : di::factory_tag<Bar> {};

struct Baz
{
    Baz(std::shared_ptr<Foo> foo, std::unique_ptr<Bar> bar)
        : foo(std::move(foo))
        , bar(std::move(bar))
    {}
    std::shared_ptr<Foo> foo;
    std::unique_ptr<Bar> bar;
};
struct BazTag : di::singleton_tag<Baz> {};

di::context createContext()
{
    auto ctx = di::context();

    ctx.registerTag<FooTag>();
    ctx.registerTag<BarTag, Bar, FooTag>();
    ctx.registerTag<BazTag, Baz, FooTag, BarTag>();

    return ctx;
}

} // anonymous namespace

TEST_CASE("Resolve a singleton tag without dependancies")
{
    auto ctx = createContext();

    const auto foo = ctx.resolve<FooTag>();

    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Resolve a singleton tag without dependancies several times")
{
    auto ctx = createContext();

    const auto foo1 = ctx.resolve<FooTag>();
    const auto foo2 = ctx.resolve<FooTag>();

    REQUIRE(foo1 == foo2);
}

TEST_CASE("Resolve a tag with one dependeny")
{
    auto ctx = createContext();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
    REQUIRE(typeid(*bar) == typeid(Bar));

    const auto foo = bar->foo;
    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Resolve a factory tag a couple of time")
{
    auto ctx = createContext();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
    REQUIRE(bar != ctx.resolve<BarTag>());
}

TEST_CASE("Resolve a tag with several dependeny")
{
    auto ctx = createContext();

    const auto baz = ctx.resolve<BazTag>();

    REQUIRE(baz != nullptr);
    REQUIRE(typeid(*baz) == typeid(Baz));
    REQUIRE(baz->foo == baz->bar->foo);
}
