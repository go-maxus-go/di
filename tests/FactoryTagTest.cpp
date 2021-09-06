#include "Common.h"


TEST_CASE("Resolving a factory tag with objects")
{
    struct Foo {};
    struct FooTag : di::factory_tag<Foo> {};

    struct Bar {
        using di_deps = FooTag;
        Bar(std::unique_ptr<Foo> foo) : foo(std::move(foo)) {}
        std::unique_ptr<Foo> foo;
    };
    struct BarTag : di::factory_tag<Bar> {};

    di::context ctx;
    ctx.registerTag<FooTag, Foo>();
    ctx.registerTag<BarTag, Bar>();

    const auto bar1 = ctx.resolve<BarTag>();
    const auto bar2 = ctx.resolve<BarTag>();

    REQUIRE(bar1.get() != bar2.get());
    REQUIRE(bar1->foo.get() != bar2->foo.get());
}

TEST_CASE("Resolving a factory tag with interfaces")
{
    struct IFoo {
        virtual ~IFoo() = default;
        virtual void fun() = 0;
    };
    struct Foo : IFoo {
        void fun() override {}
    };
    struct FooTag : di::factory_tag<IFoo> {};

    struct IBar {
        virtual ~IBar() = default;
        virtual IFoo* ifoo() const = 0;
    };
    struct Bar : IBar {
        using di_deps = FooTag;
        Bar(std::unique_ptr<IFoo> foo) : foo(std::move(foo)) {}
        IFoo* ifoo() const override { return foo.get(); }
        std::unique_ptr<IFoo> foo;
    };
    struct BarTag : di::factory_tag<IBar> {};

    di::context ctx;
    ctx.registerTag<FooTag, Foo>();
    ctx.registerTag<BarTag, Bar>();

    const auto bar1 = ctx.resolve<BarTag>();
    const auto bar2 = ctx.resolve<BarTag>();

    REQUIRE(bar1.get() != bar2.get());
    REQUIRE(bar1->ifoo() != bar2->ifoo());
}
