#pragma once

#include "details/fwd.h"
#include "details/context_imp.h"

#include "fwd.h"


namespace di {

namespace details {

template<class TYPE, class ... TAGS>
auto creatorFromTags(const di::Context & ctx, std::tuple<TAGS...>);

template<class TYPE>
auto defaultCreator(const di::Context & ctx);

} // details

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

public:
    template<class TAG, class TYPE>
    void registerTag()
    {
        registerTag<TAG>([](const auto & ctx) {
            return details::defaultCreator<TYPE>(ctx);
        });
    }

    template<class TAG, class TYPE, class ... TAGS>
    void registerTag(std::tuple<TAGS...> tags)
    {
        registerTag<TAG>([&tags](const auto & ctx) {
            return details::creatorFromTags<TYPE>(ctx, tags);
        });
    }

    template<class TAG>
    void registerTag(Creator<TAG> creator)
    {
        m_impl->registerTag<TAG>(std::move(creator));
    }

    template<class TAG>
    void registerTransientTag(Creator<TAG> creator)
    {
        m_impl->registerTransientTag<TAG>(std::move(creator));
    }

    template<class TAG, class TYPE>
    void registerTransientTag()
    {
        registerTransientTag<TAG>([](const auto & ctx) {
            return details::defaultCreator<TYPE>(ctx);
        });
    }

    template<class TAG, class TYPE, class ... TAGS>
    void registerTransientTag(std::tuple<TAGS...> tags)
    {
        registerTransientTag<TAG>([&tags](const auto & ctx) {
            return details::creatorFromTags<TYPE>(ctx, tags);
        });
    }

    template<class TAG>
    ObjectPtr<TAG> resolve() const
    {
        return m_impl->resolve<TAG>(*this);
    }

private:
    ContextImplPtr m_impl;
};

namespace details {

template<class TYPE, class ... TAGS>
auto creatorFromTags(const di::Context & ctx, std::tuple<TAGS...>)
{
    return std::make_shared<TYPE>((ctx.resolve<TAGS>())...);
}

template<class TYPE>
auto defaultCreator(const di::Context & ctx)
{
    return creatorFromTags<TYPE>(ctx, typename TYPE::di());
}

} // details

} // namespace di
