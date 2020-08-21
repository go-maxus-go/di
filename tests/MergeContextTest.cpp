#include "Common.h"


namespace {

const auto testArg = "[MergeContextTest]";

struct Foo {};
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

} // anonymous namespace

TEST_CASE("Merge two contexts", testArg)
{
    auto ctxFoo = di::context();
    ctxFoo.registerTag<FooTag, Foo>();

    const auto foo = ctxFoo.resolve<FooTag>();
    REQUIRE(foo != nullptr);

    auto ctx = di::context();
    ctx += std::move(ctxFoo);

    try {
        ctxFoo.resolve<FooTag>();
        REQUIRE(false);
    }
    catch (const std::logic_error &) {
    }

    REQUIRE(foo == ctx.resolve<FooTag>());
}

TEST_CASE("Resolve dependenies after the merge", testArg)
{
    auto ctxFoo = di::context();
    ctxFoo.registerTag<FooTag, Foo>();

    auto ctxBar = di::context();
    ctxBar.registerTag<BarTag, Bar>();

    try {
        ctxBar.resolve<BarTag>();
        REQUIRE(false);
    }
    catch (const std::logic_error &) {
    }

    ctxBar += std::move(ctxFoo);
    REQUIRE(ctxBar.resolve<BarTag>() != nullptr);
}

TEST_CASE("The moved context is empty after the merge", testArg)
{
    auto ctxFoo = di::context();
    ctxFoo.registerTag<FooTag, Foo>();

    REQUIRE(ctxFoo.resolve<FooTag>() != nullptr);

    auto ctxBar = di::context();
    ctxBar.registerTag<BarTag, Bar>();
    ctxBar += std::move(ctxFoo);

    try {
        ctxFoo.resolve<FooTag>();
        REQUIRE(false);
    }
    catch (const std::logic_error &) {
    }
}

TEST_CASE("The normal usage", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<BarTag, Bar>();
    ctx += []{
        auto ctxFoo = di::context();
        ctxFoo.registerTag<FooTag, Foo>();
        return ctxFoo;
    }();

    REQUIRE(ctx.resolve<BarTag>() != nullptr);
}
