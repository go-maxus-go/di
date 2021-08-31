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
struct BarTag : di::singleton_tag<Bar> {};

struct Baz {};
struct BazTag : di::factory_tag<Baz> {};

struct Qux {
    Qux(std::unique_ptr<Baz> baz)
        : baz(std::move(baz))
    {}
    std::shared_ptr<Baz> baz;
};
struct QuxTag : di::factory_tag<Qux> {};

di::context createContext()
{
    auto ctx = di::context();

    ctx.registerTag<FooTag>([](const auto &) {
        return std::make_unique<Foo>();
    });
    ctx.registerTag<BarTag>([](const di::context & ctx) {
        return std::make_unique<Bar>(ctx.resolve<FooTag>());
    });
    ctx.registerTag<BazTag>([](const auto &) {
        return std::make_unique<Baz>();
    });
    ctx.registerTag<QuxTag>([](const di::context & ctx) {
        return std::make_unique<Qux>(ctx.resolve<BazTag>());
    });

    return ctx;
}

} // anonymous namespace

TEST_CASE("Register tag and resolve it")
{
    auto ctx = createContext();

    const auto foo = ctx.resolve<FooTag>();

    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Register tag and resolve it several times")
{
    auto ctx = createContext();

    const auto foo1 = ctx.resolve<FooTag>();
    const auto foo2 = ctx.resolve<FooTag>();

    REQUIRE(foo1 == foo2);
}

TEST_CASE("Register a couple of tag and resolve it")
{
    auto ctx = createContext();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
    REQUIRE(typeid(*bar) == typeid(Bar));

    const auto foo = bar->foo;
    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(Foo));
}

TEST_CASE("Context destruction releases objects")
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

TEST_CASE("Factory tag registering and resolving ")
{
    auto ctx = createContext();

    const auto baz1 = ctx.resolve<BazTag>();
    const std::unique_ptr<Baz> baz2 = ctx.resolve<BazTag>();

    REQUIRE(baz1 != baz2);

    REQUIRE(baz1 != nullptr);
    REQUIRE(typeid(*baz1) == typeid(Baz));

    REQUIRE(baz2 != nullptr);
    REQUIRE(typeid(*baz2) == typeid(Baz));
}

TEST_CASE("Factory tag registering and resolving a dependent class")
{
    auto ctx = createContext();

    const auto qux = ctx.resolve<QuxTag>();

    REQUIRE(qux != nullptr);
    REQUIRE(qux->baz != nullptr);
    REQUIRE(typeid(*qux) == typeid(Qux));
}
