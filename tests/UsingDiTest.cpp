#include "Common.h"


namespace {

const auto testArg = "[UsingDiTest]";

struct EmptyNoDi {};
struct EmptyNoDiTag : di::singleton_tag<EmptyNoDi> {};

struct EmptyWithDi {
    using di = std::tuple<>;
};
struct EmptyWithDiTag : di::factory_tag<EmptyWithDi> {};

struct Dependent {
    using di = std::tuple<EmptyNoDiTag, EmptyWithDiTag>;
    Dependent(std::shared_ptr<EmptyNoDi> emptyNoDi, std::unique_ptr<EmptyWithDi> emptyWithDi)
        : emptyNoDi(std::move(emptyNoDi))
        , emptyWithDi(std::move(emptyWithDi))
    {}

    Dependent(std::shared_ptr<EmptyNoDi> emptyNoDi)
        : emptyNoDi(std::move(emptyNoDi))
    {}

    std::shared_ptr<EmptyNoDi> emptyNoDi;
    std::unique_ptr<EmptyWithDi> emptyWithDi;
};
struct DependentTag : di::singleton_tag<Dependent> {};

struct SingleDependent {
    using di = EmptyNoDiTag;
    SingleDependent(std::shared_ptr<EmptyNoDi> emptyNoDi)
        : emptyNoDi(std::move(emptyNoDi))
    {}
    std::shared_ptr<EmptyNoDi> emptyNoDi;
};
struct SingleDependentTag : di::singleton_tag<SingleDependent> {};

} // anonymous namespace

TEST_CASE("Use default constructor if no di is prodived", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();

    REQUIRE(ctx.resolve<EmptyNoDiTag>() != nullptr);
    REQUIRE(ctx.resolve<EmptyNoDiTag>() == ctx.resolve<EmptyNoDiTag>());
}

TEST_CASE("Use default constructor if no di is prodived for a factory tag", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();

    REQUIRE(ctx.resolve<EmptyWithDiTag>() != nullptr);
    REQUIRE(ctx.resolve<EmptyWithDiTag>() != ctx.resolve<EmptyWithDiTag>());
}

TEST_CASE("Use di from the implementation", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();
    ctx.registerTag<DependentTag, Dependent>();

    const auto dependent = ctx.resolve<DependentTag>();
    REQUIRE(dependent != nullptr);
    REQUIRE(dependent == ctx.resolve<DependentTag>());
    REQUIRE(dependent->emptyNoDi != nullptr);
    REQUIRE(dependent->emptyWithDi != nullptr);
}

TEST_CASE("Overwrite the implementation di tags", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();
    ctx.registerTag<DependentTag, Dependent, EmptyNoDiTag>();

    const auto dependent = ctx.resolve<DependentTag>();
    REQUIRE(dependent != nullptr);
    REQUIRE(dependent == ctx.resolve<DependentTag>());
    REQUIRE(dependent->emptyNoDi != nullptr);
    REQUIRE(dependent->emptyWithDi == nullptr);
}

TEST_CASE("Use one tag type di", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<SingleDependentTag, SingleDependent>();

    REQUIRE(ctx.resolve<SingleDependentTag>() != nullptr);
    REQUIRE(ctx.resolve<SingleDependentTag>() == ctx.resolve<SingleDependentTag>());
}
