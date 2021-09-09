#include "Common.h"


namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

TEST_CASE("Resolve an abstract reference tag with dependencies in the context")
{
    struct IBar {
        virtual ~IBar() = default;
        virtual void fun() = 0;
    };
    struct Bar : IBar {
        Bar(std::shared_ptr<Foo>) {}
        void fun() override {}
    };
    struct BarTag : di::singleton_tag<Bar> {};

    di::context ctx;
    ctx.put<FooTag>();
    ctx.put<BarTag, Bar, FooTag>();

    REQUIRE(ctx.resolve<BarTag>() != nullptr);
}

TEST_CASE("Resolve a concrete reference tag with dependencies in the context")
{
    struct Bar {
        Bar(std::shared_ptr<Foo>) {}
    };
    struct BarTag : di::singleton_tag<Bar> {};

    di::context ctx;
    ctx.put<FooTag>();
    ctx.put<BarTag, FooTag>();

    REQUIRE(ctx.resolve<BarTag>() != nullptr);
}

} // anonymous namespace
