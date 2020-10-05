#pragma once

#include "fwd.h"

#include "Details/Fwd.h"
#include "Details/ContextImpl.h"
#include "Details/HasMemberDi.h"


namespace di {

/*
 * The main class for dealing with dependenies.
 */
class context
{
    using ContextImpl = Details::ContextImpl;
    using ContextImplPtr = std::shared_ptr<ContextImpl>;

    template<class TAG> using CreatorByTag = Details::CreatorByTag<TAG>;
    template<class TYPE> using CreatorByType = Details::CreatorByType<TYPE>;

public:
    context()
        : m_impl(std::make_shared<ContextImpl>())
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
     * Register a singleton DI tag.
     * The resolved value will get dependencies from the TYPE "di" tag list.
     * If the "di" tag list is not provided the empty constructor will be used.
     */
    template<class TAG, class TYPE>
    void registerTag()
    {
        registerTag<TAG>([](const auto & ctx) {
            constexpr auto hasDi = Details::has_member_di<TYPE>::value;
            return creatorFromType<TYPE>(ctx, std::integral_constant<bool, hasDi>());
        });
    }

    /*
     * Register a singleton DI tag.
     * The resolved value will get dependencies from the provided tag list.
     * The TYPE "di" tag list will be overwritten.
     */
    template<class TAG, class TYPE, class ... TAGS>
    void registerTag(std::tuple<TAGS...>* tags)
    {
        registerTag<TAG>([&tags](const auto & ctx) {
            return creatorFromTags<TYPE>(ctx, tags);
        });
    }

    /*
     * Register a singleton DI tag.
     * For creation of the TYPE the provided creator function will be used.
     */
    template<class TAG>
    void registerTag(CreatorByTag<TAG> creator)
    {
        m_impl->registerTag<TAG>(std::move(creator));
    }

    /*
     * Register a factory DI tag.
     * The resolved value will get dependencies from the TYPE "di" tag list.
     * If the "di" tag list is not provided the empty constructor will be used.
     */
    template<class TAG>
    void registerFactoryTag(CreatorByTag<TAG> creator)
    {
        m_impl->registerFactoryTag<TAG>(std::move(creator));
    }

    /*
     * Register a factory DI tag.
     * The resolved value will get dependencies from the provided tag list.
     * The TYPE "di" tag list will be overwritten.
     */
    template<class TAG, class TYPE>
    void registerFactoryTag()
    {
        registerFactoryTag<TAG>([](const auto & ctx) {
            constexpr auto hasDi = Details::has_member_di<TYPE>::value;
            return creatorFromType<TYPE>(ctx, std::integral_constant<bool, hasDi>());
        });
    }

    /*
     * Register a factory DI tag.
     * For creation of the TYPE the provided creator function will be used.
     */
    template<class TAG, class TYPE, class ... TAGS>
    void registerFactoryTag(std::tuple<TAGS...>* tags)
    {
        registerFactoryTag<TAG>([&tags](const auto & ctx) {
            return creatorFromTags<TYPE>(ctx, tags);
        });
    }

    /*
     */
    template<class TYPE, class IMPL>
    void registerType()
    {
        registerType<TYPE>([](const auto & ctx) {
            constexpr auto hasDi = Details::has_member_di<IMPL>::value;
            return creatorFromType<IMPL>(ctx, std::integral_constant<bool, hasDi>());
        });
    }

    /*
     */
    template<class TYPE, class IMPL, class ... TAGS>
    void registerType(std::tuple<TAGS...>* tags)
    {
        registerType<TYPE>([&tags](const auto & ctx) {
            return creatorFromTags<IMPL>(ctx, tags);
        });
    }

    template<class TYPE>
    void registerType(CreatorByType<TYPE> creator)
    {
        m_impl->registerType(std::move(creator));
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
    static constexpr auto creatorFromTags(const di::context & ctx, std::tuple<TAGS...>*)
    {
        return std::make_shared<TYPE>((ctx.resolve<TAGS>())...);
    }

    template<class TYPE, class TAG>
    static constexpr auto creatorFromTags(const di::context & ctx, TAG*)
    {
        return std::make_shared<TYPE>(ctx.resolve<TAG>());
    }

    template<class TYPE>
    static constexpr auto creatorFromType(const di::context & ctx, std::true_type)
    {
        return creatorFromTags<TYPE>(ctx, (typename TYPE::di*)(nullptr));
    }

    template<class TYPE>
    static constexpr auto creatorFromType(const di::context &, std::false_type)
    {
        return std::make_shared<TYPE>();
    }

private:
    ContextImplPtr m_impl;
};

} // namespace di
