#include "Common.h"


namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

struct IQux
{
    virtual ~IQux() = default;
    virtual void fun() = 0;
};

TEST_CASE("Resolve an abstract reference tag with one tag di_deps as a type")
{
    struct Qux : IQux {
        using di_deps = FooTag;
        Qux(std::shared_ptr<Foo>) {}
        void fun() override {}
    };
    struct QuxTag : di::singleton_tag<IQux> {};

    di::context ctx;
    ctx.put<FooTag>();
    ctx.put<QuxTag, Qux>();

    REQUIRE(ctx.resolve<QuxTag>() != nullptr);
}

TEST_CASE("Resolve an abstract reference tag with one tag in di_deps tuple")
{
    struct Qux : IQux {
        using di_deps = std::tuple<FooTag>;
        Qux(std::shared_ptr<Foo>) {}
        void fun() override {}
    };
    struct QuxTag : di::singleton_tag<IQux> {};

    di::context ctx;
    ctx.put<FooTag>();
    ctx.put<QuxTag, Qux>();

    REQUIRE(ctx.resolve<QuxTag>() != nullptr);
}

TEST_CASE("Resolve an abstract reference tag with several tags in di_deps")
{
    struct Bar {};
    struct BarTag : di::singleton_tag<Bar> {};

    struct Qux : IQux {
        using di_deps = std::tuple<FooTag, BarTag>;
        Qux(std::shared_ptr<Foo>, std::shared_ptr<Bar>) {}
        void fun() override {}
    };
    struct QuxTag : di::singleton_tag<IQux> {};

    di::context ctx;
    ctx.put<FooTag>();
    ctx.put<BarTag>();
    ctx.put<QuxTag, Qux>();

    REQUIRE(ctx.resolve<QuxTag>() != nullptr);
}

} // anonymous namespace
