//#include "Common.h"


//namespace {

//struct Foo {};
//struct FooTag : di::singleton_tag<Foo> {};

//struct Bar {
//    using di_deps = std::tuple<FooTag>;
//    Bar(std::shared_ptr<Foo> foo)
//        : foo(std::move(foo))
//    {}
//    std::shared_ptr<Foo> foo;
//};
//struct BarTag : di::singleton_tag<Bar> {};

//} // anonymous namespace

//TEST_CASE("Merge two contexts")
//{
//    auto ctxFoo = di::context();
//    ctxFoo.registerTag<FooTag, Foo>();

//    const auto foo = ctxFoo.resolve<FooTag>();
//    REQUIRE(foo != nullptr);

//    auto ctx = di::context();
//    ctx += std::move(ctxFoo);

//    try {
//        ctxFoo.resolve<FooTag>();
//        REQUIRE(false);
//    }
//    catch (const std::logic_error &) {
//    }

//    REQUIRE(foo == ctx.resolve<FooTag>());
//}

//TEST_CASE("Resolve dependenies after the merge")
//{
//    auto ctxFoo = di::context();
//    ctxFoo.registerTag<FooTag, Foo>();

//    auto ctxBar = di::context();
//    ctxBar.registerTag<BarTag, Bar>();

//    try {
//        ctxBar.resolve<BarTag>();
//        REQUIRE(false);
//    }
//    catch (const std::logic_error &) {
//    }

//    ctxBar += std::move(ctxFoo);
//    REQUIRE(ctxBar.resolve<BarTag>() != nullptr);
//}

//TEST_CASE("The moved context is empty after the merge")
//{
//    auto ctxFoo = di::context();
//    ctxFoo.registerTag<FooTag, Foo>();

//    REQUIRE(ctxFoo.resolve<FooTag>() != nullptr);

//    auto ctxBar = di::context();
//    ctxBar.registerTag<BarTag, Bar>();
//    ctxBar += std::move(ctxFoo);

//    try {
//        ctxFoo.resolve<FooTag>();
//        REQUIRE(false);
//    }
//    catch (const std::logic_error &) {
//    }
//}

//TEST_CASE("The normal usage")
//{
//    auto ctx = di::context();
//    ctx.registerTag<BarTag, Bar>();
//    ctx += []{
//        auto ctxFoo = di::context();
//        ctxFoo.registerTag<FooTag, Foo>();
//        return ctxFoo;
//    }();

//    REQUIRE(ctx.resolve<BarTag>() != nullptr);
//}
