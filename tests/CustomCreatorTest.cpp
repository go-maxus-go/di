#include "Common.h"


TEST_CASE("Custom creator resolves an object tag")
{
    struct Foo {};
    struct FooTag : di::singleton_tag<Foo> {};

    di::context ctx;
    ctx.registerTag<FooTag>([](const di::context&) {
        return std::make_unique<Foo>();
    });

    const auto foo = ctx.resolve<FooTag>();
    REQUIRE(foo != nullptr);
}

TEST_CASE("Custom creator resolves an interface tag")
{
    struct IFoo {};
    struct Foo : IFoo {};
    struct FooTag : di::singleton_tag<IFoo> {};

    di::context ctx;
    ctx.registerTag<FooTag>([](const di::context&) {
        return std::make_unique<Foo>();
    });

    const auto foo = ctx.resolve<FooTag>();
    REQUIRE(foo != nullptr);
    REQUIRE(typeid(*foo) == typeid(IFoo));
}
