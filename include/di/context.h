#pragma once

#include "fwd.h"

#include "Details/Fwd.h"
#include "Details/ContextImpl.h"
#include "Details/HasMemberDi.h"


namespace di {

/*
 * The main class for dealing with dependenies.
 * It's supposed to be filled with all dependencies on application start event.
 * When it is filled with all dependencies it is ready to use.
 */
class context
{
    using ContextImpl = Details::ContextImpl;
    using ContextImplPtr = std::unique_ptr<ContextImpl>;

    template<class TAG> using Creator = Details::Creator<TAG>;

public:
    context()
        : m_impl(std::make_unique<ContextImpl>())
    {}

    context(const context & ctx) = delete;
    context(context && ctx)
        : m_impl(std::move(ctx.m_impl))
    {}

    context & operator = (const context &) = delete;
    context & operator = (context && ctx)
    {
        m_impl = std::move(ctx.m_impl);
        return *this;
    }

public:
    /*
     * Merge two contexts. The origin context will get all from the moved one.
     * The moved context overwrites dependencies if the same tag is used.
     * After the merge the moved context will be empty.
     */
    context & operator += (context && ctx)
    {
        *m_impl += std::move(*ctx.m_impl);
        return *this;
    }

    /*
     * Register a DI tag.
     * The resolved value will get dependencies from the provided tags or the TYPE "di".
     * The "di" tag list will be overwritten by TAGS provided to the function.
     */
    template<class TAG, class TYPE, class ... TAGS>
    void registerTag()
    {
        registerTag<TAG>([](const ::di::context & ctx) {
            constexpr auto tagsCount = std::tuple_size<std::tuple<TAGS...>>::value;
            constexpr auto hasDi = Details::has_member_di<TYPE>::value;
            constexpr auto useDi = tagsCount == 0 && hasDi;
            constexpr std::tuple<TAGS...> * dependency = nullptr;
            return creatorFromTags<TYPE>(ctx, dependency, std::integral_constant<bool, useDi>());
        });
    }

    /*
     * Register a DI tag for a non abstract type.
     */
    template<class TAG>
    void registerTag()
    {
        registerTag<TAG, Details::Type<TAG>>();
    }

    /*
     * Register a DI tag with specification of a creator function.
     * NOTE: all creator functions must return std::unique_ptr<TYPE>
     * where TYPE is specified in the tag.
     */
    template<class TAG>
    void registerTag(Creator<TAG> creator)
    {
        m_impl->registerTag<TAG>(std::move(creator));
    }

    /*
     * Try to resolve all dependencies and provide the result object.
     * For a singleton tag the same object will be returned everytime.
     * For a factory tag a new object will be returned for each function call.
     */
    template<class TAG>
    auto resolve() const
    {
        return m_impl->resolve<TAG>(*this);
    }

private:
    template<class TYPE, class ... TAGS>
    static constexpr auto creatorFromTags(
            const di::context & ctx,
            const std::tuple<TAGS...>*,
            std::true_type)
    {
        constexpr typename TYPE::di * dependency = nullptr;
        return creatorFromTags<TYPE>(ctx, dependency, std::false_type());
    }

    template<class TYPE, class TAG>
    static constexpr auto creatorFromTags(
            const di::context & ctx,
            const TAG *,
            std::false_type)
    {
        constexpr std::tuple<TAG> * dependency = nullptr;
        return creatorFromTags<TYPE>(ctx, dependency, std::false_type());
    }

    template<class TYPE, class ... TAGS>
    static constexpr auto creatorFromTags(
            const di::context & ctx,
            const std::tuple<TAGS...>*,
            std::false_type)
    {
        return std::make_unique<TYPE>((ctx.resolve<TAGS>())...);
    }

private:
    ContextImplPtr m_impl;
};

} // namespace di
