#pragma once

#include "details/fwd.h"
#include "details/context_imp.h"

#include "fwd.h"

#include <type_traits> // To use 'std::integral_constant'.

#define GENERATE_HAS_MEMBER(member)                                               \
                                                                                  \
template < class T >                                                              \
class HasMember_##member                                                          \
{                                                                                 \
private:                                                                          \
    using Yes = char[2];                                                          \
    using  No = char[1];                                                          \
                                                                                  \
    struct Fallback { int member; };                                              \
    struct Derived : T, Fallback { };                                             \
                                                                                  \
    template < class U >                                                          \
    static No& test ( decltype(U::member)* );                                     \
    template < typename U >                                                       \
    static Yes& test ( U* );                                                      \
                                                                                  \
public:                                                                           \
    static constexpr bool RESULT = sizeof(test<Derived>(nullptr)) == sizeof(Yes); \
};                                                                                \
                                                                                  \
template < class T >                                                              \
struct has_member_##member                                                        \
: public std::integral_constant<bool, HasMember_##member<T>::RESULT>              \
{                                                                                 \
};

GENERATE_HAS_MEMBER(di)  // Creates 'has_member_di'.


namespace di {

class Context
{
    using ContextImpl = details::ContextImpl;
    using ContextImplPtr = std::shared_ptr<ContextImpl>;

    template<class TAG> using Creator = details::Creator<TAG>;
    template<class TAG> using ObjectPtr = details::ObjectPtr<TAG>;

public:
    Context()
        : m_impl(std::make_shared<ContextImpl>())
    {}

    Context(const Context & ctx) = delete;
    Context(Context && ctx)
        : m_impl(std::move(ctx.m_impl))
    {}

    Context & operator = (const Context &) = delete;
    Context & operator = (Context && ctx)
    {
        m_impl = std::move(ctx.m_impl);
        return *this;
    }

    Context & operator += (Context && ctx)
    {
        *m_impl += std::move(*ctx.m_impl);
        return *this;
    }

public:
    template<class TAG, class TYPE>
    void registerTag()
    {
        registerTag<TAG>([](const auto & ctx) {
            return creatorFromDi<TYPE>(ctx, std::integral_constant<bool, has_member_di<TYPE>::value>());
        });
    }

    template<class TAG, class TYPE, class ... TAGS>
    void registerTag(std::tuple<TAGS...> tags)
    {
        registerTag<TAG>([&tags](const auto & ctx) {
            return creatorFromTags<TYPE>(ctx, tags);
        });
    }

    template<class TAG>
    void registerTag(Creator<TAG> creator)
    {
        m_impl->registerTag<TAG>(std::move(creator));
    }

    template<class TAG>
    void registerFactoryTag(Creator<TAG> creator)
    {
        m_impl->registerTransientTag<TAG>(std::move(creator));
    }

    template<class TAG, class TYPE>
    void registerFactoryTag()
    {
        registerFactoryTag<TAG>([](const auto & ctx) {
            return creatorFromDi<TYPE>(ctx, std::integral_constant<bool, has_member_di<TYPE>::value>());
        });
    }

    template<class TAG, class TYPE, class ... TAGS>
    void registerFactoryTag(std::tuple<TAGS...> tags)
    {
        registerFactoryTag<TAG>([&tags](const auto & ctx) {
            return creatorFromTags<TYPE>(ctx, tags);
        });
    }

    template<class TAG>
    ObjectPtr<TAG> resolve() const
    {
        return m_impl->resolve<TAG>(*this);
    }

private:
    template<class TYPE, class ... TAGS>
    static auto creatorFromTags(const di::Context & ctx, std::tuple<TAGS...>)
    {
        return std::make_shared<TYPE>((ctx.resolve<TAGS>())...);
    }

    template<class TYPE>
    static auto creatorFromDi(const di::Context & ctx, std::true_type)
    {
        return creatorFromTags<TYPE>(ctx, typename TYPE::di());
    }

    template<class TYPE>
    static auto creatorFromDi(const di::Context &, std::false_type)
    {
        return std::make_shared<TYPE>();
    }

private:
    ContextImplPtr m_impl;
};

} // namespace di
