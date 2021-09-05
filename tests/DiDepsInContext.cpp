#include "Common.h"

namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

} // anonymous namespace

TEST_CASE("Resolve an interface with tags in the context")
{
    struct IBar {};
    struct Bar : IBar {
        Bar(std::shared_ptr<Foo>) {}
    };
    struct BarTag : di::singleton_tag<Bar> {};

    di::context ctx;
    ctx.registerTag<FooTag>();
    ctx.registerTag<BarTag, Bar, FooTag>();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
}

TEST_CASE("Resolve an object with tags in the context")
{
    struct Bar {
        Bar(std::shared_ptr<Foo>) {}
    };
    struct BarTag : di::singleton_tag<Bar> {};

    di::context ctx;
    ctx.registerTag<FooTag>();
    ctx.registerTag<BarTag, FooTag>();

    const auto bar = ctx.resolve<BarTag>();
    REQUIRE(bar != nullptr);
}
