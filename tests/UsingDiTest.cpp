#include "Common.h"


namespace {

const auto testArg = "[UsingDiTest]";

struct EmptyNoDi {};
using EmptyNoDiPtr = Ptr<EmptyNoDi>;
DECLARE_DI_TAG(EmptyNoDiTag, EmptyNoDi);

struct EmptyWithDi {
    using di = std::tuple<>;
};
using EmptyWithDiPtr  = Ptr<EmptyWithDi >;
DECLARE_DI_TAG(EmptyWithDiTag, EmptyWithDi );

struct Dependent {
    using di = std::tuple<EmptyNoDiTag, EmptyWithDiTag>;
    Dependent(EmptyNoDiPtr emptyNoDi, EmptyWithDiPtr emptyWithDi)
        : emptyNoDi(std::move(emptyNoDi))
        , emptyWithDi(std::move(emptyWithDi))
    {}

    Dependent(EmptyNoDiPtr emptyNoDi)
        : emptyNoDi(std::move(emptyNoDi))
    {}
    EmptyNoDiPtr emptyNoDi;
    EmptyWithDiPtr emptyWithDi;
};
using DependentPtr = Ptr<Dependent>;
DECLARE_DI_TAG(DependentTag, Dependent);

struct SingleDependent {
    using di = EmptyNoDiTag;
    SingleDependent(EmptyNoDiPtr emptyNoDi)
        : emptyNoDi(std::move(emptyNoDi))
    {}
    EmptyNoDiPtr emptyNoDi;
};
using SingleDependentPtr = Ptr<SingleDependent>;
DECLARE_DI_TAG(SingleDependentTag, SingleDependent);

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
    ctx.registerFactoryTag<EmptyNoDiTag, EmptyNoDi>();

    REQUIRE(ctx.resolve<EmptyNoDiTag>() != nullptr);
    REQUIRE(ctx.resolve<EmptyNoDiTag>() != ctx.resolve<EmptyNoDiTag>());
}

TEST_CASE("Use default constructor if empty di is prodived", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();

    REQUIRE(ctx.resolve<EmptyWithDiTag>() != nullptr);
    REQUIRE(ctx.resolve<EmptyWithDiTag>() == ctx.resolve<EmptyWithDiTag>());
}

TEST_CASE("Use default constructor if empty di is prodived for a factory tag", testArg)
{
    auto ctx = di::context();
    ctx.registerFactoryTag<EmptyWithDiTag, EmptyWithDi>();

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

TEST_CASE("Use di from the implementation for a factory tag", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();
    ctx.registerFactoryTag<DependentTag, Dependent>();

    const auto dependent = ctx.resolve<DependentTag>();
    REQUIRE(dependent != nullptr);
    REQUIRE(dependent != ctx.resolve<DependentTag>());
    REQUIRE(dependent->emptyNoDi != nullptr);
    REQUIRE(dependent->emptyWithDi != nullptr);
}

TEST_CASE("Overwrite the implementation di tags", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();
    ctx.registerTag<DependentTag, Dependent>((std::tuple<EmptyNoDiTag>*)(nullptr));

    const auto dependent = ctx.resolve<DependentTag>();
    REQUIRE(dependent != nullptr);
    REQUIRE(dependent == ctx.resolve<DependentTag>());
    REQUIRE(dependent->emptyNoDi != nullptr);
    REQUIRE(dependent->emptyWithDi == nullptr);
}

TEST_CASE("Overwrite the implementation di tags for a factory tag", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerTag<EmptyWithDiTag, EmptyWithDi>();
    ctx.registerFactoryTag<DependentTag, Dependent>((std::tuple<EmptyNoDiTag>*)(nullptr));

    const auto dependent = ctx.resolve<DependentTag>();
    REQUIRE(dependent != nullptr);
    REQUIRE(dependent != ctx.resolve<DependentTag>());
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

TEST_CASE("Use one tag type di for a factory tag", testArg)
{
    auto ctx = di::context();
    ctx.registerTag<EmptyNoDiTag, EmptyNoDi>();
    ctx.registerFactoryTag<SingleDependentTag, SingleDependent>();

    REQUIRE(ctx.resolve<SingleDependentTag>() != nullptr);
    REQUIRE(ctx.resolve<SingleDependentTag>() != ctx.resolve<SingleDependentTag>());
}
