#include "Common.h"


namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

TEST_CASE("An exception is thrown if singleton custom creator returns null")
{
    di::context ctx;
    ctx.put<FooTag>([](const di::context&) {
        return nullptr;
    });

    REQUIRE_THROWS(ctx.resolve<FooTag>());
}

TEST_CASE("An exception is thrown if factory custom creator returns null")
{
    struct FooTag : di::factory_tag<Foo> {};

    di::context ctx;
    ctx.put<FooTag>([](const di::context&) {
        return nullptr;
    });

    REQUIRE_THROWS(ctx.resolve<FooTag>());
}

TEST_CASE("Custom creator resolves an object tag using make_unique")
{
    di::context ctx;
    ctx.put<FooTag>([](const di::context&) {
        return std::make_unique<Foo>();
    });

    REQUIRE(ctx.resolve<FooTag>() != nullptr);
}

TEST_CASE("Custom creator resolves an object tag using make_shared")
{
    di::context ctx;
    ctx.put<FooTag>([](const di::context&) {
        return std::make_shared<Foo>();
    });

    REQUIRE(ctx.resolve<FooTag>() != nullptr);
}

TEST_CASE("Custom creator resolves an interface tag")
{
    struct IFoo {
        virtual ~IFoo() = default;
        virtual void fun() = 0;
    };
    struct Foo : IFoo {
        void fun() override {}
    };
    struct FooTag : di::singleton_tag<IFoo> {};

    di::context ctx;
    ctx.put<FooTag>([](const di::context&) {
        return std::make_shared<Foo>();
    });

    const auto foo = ctx.resolve<FooTag>();
    REQUIRE(foo != nullptr);
    REQUIRE(typeid(foo.get()) == typeid(IFoo*));
}

} // anonymous namespace
