#include "Common.h"


namespace {

struct Foo {};
struct FooTag : di::singleton_tag<Foo> {};

struct Bar {
    int id = 0;
};
struct BarTag : di::singleton_tag<Bar> {};

} // anonymous namespace

TEST_CASE("Resolving of unregistered tag throws")
{
    di::context ctx;
    REQUIRE_THROWS(ctx.resolve<FooTag>());
}

TEST_CASE("Move constructor leaves an empty context")
{
    di::context ctx;
    ctx.put<FooTag>();

    auto newCtx = std::move(ctx);

    REQUIRE(newCtx.resolve<FooTag>() != nullptr);
    REQUIRE_THROWS(ctx.resolve<FooTag>());
}

TEST_CASE("Assignment operator leaves an empty context")
{
    di::context ctx;
    ctx.put<FooTag>();

    di::context newCtx;
    newCtx = std::move(ctx);

    REQUIRE(newCtx.resolve<FooTag>() != nullptr);
    REQUIRE_THROWS(ctx.resolve<FooTag>());
}

TEST_CASE("Addition assignment operator merges two contexts")
{
    di::context ctx1;
    ctx1.put<FooTag>();

    di::context ctx2;
    ctx2.put<BarTag>();

    ctx1 += std::move(ctx2);

    REQUIRE(ctx1.resolve<FooTag>() != nullptr);
    REQUIRE(ctx1.resolve<BarTag>() != nullptr);
    REQUIRE_THROWS(ctx2.resolve<FooTag>());
    REQUIRE_THROWS(ctx2.resolve<BarTag>());
}

TEST_CASE("Merged context overwrites tags")
{
    di::context ctx1;
    ctx1.put<BarTag>();

    di::context ctx2;
    ctx2.put<BarTag>([](auto&&) {
        auto bar = std::make_unique<Bar>();
        bar->id = 1;
        return bar;
    });

    ctx1 += std::move(ctx2);

    REQUIRE(ctx1.resolve<BarTag>()->id == 1);
}

TEST_CASE("Tags can be overwritten before they are resolved")
{
    di::context ctx;
    ctx.put<BarTag>();
    ctx.put<BarTag>([](auto&&) {
        auto bar = std::make_unique<Bar>();
        bar->id = 1;
        return bar;
    });

    REQUIRE(ctx.resolve<BarTag>()->id == 1);
}

TEST_CASE("Tags can't be overwritten after they are resolved")
{
    di::context ctx;
    ctx.put<BarTag>();
    ctx.resolve<BarTag>();

    REQUIRE_THROWS(ctx.put<BarTag>());
}

TEST_CASE("Context destruction releases singleton objects")
{
    std::weak_ptr<Foo> weakPtr;
    {
        di::context ctx;
        ctx.put<FooTag>();

        const auto foo = ctx.resolve<FooTag>();
        REQUIRE(foo.use_count() == 2);

        weakPtr = std::weak_ptr<Foo>(foo);
    }
    REQUIRE(weakPtr.lock() == nullptr);
}
