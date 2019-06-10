#pragma once

#include "details/fwd.h"
#include "details/context_imp.h"

#include "fwd.h"


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
        , m_cleanup(true)
    {}

    Context(const Context & ctx)
        : m_impl(ctx.m_impl)
        , m_cleanup(false)
    {}

    Context(Context && ctx)
        : m_impl(std::move(ctx.m_impl))
        , m_cleanup(ctx.m_cleanup)
    {}

    ~Context()
    {
        if (m_cleanup)
            m_impl->clear();
    }

    Context & operator = (const Context &) = delete;
    Context & operator = (Context && ctx)
    {
        m_impl = std::move(ctx.m_impl);
        m_cleanup = ctx.m_cleanup;
        return *this;
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

    template<class TAG>
    ObjectPtr<TAG> resolve() const
    {
        return m_impl->resolve<TAG>();
    }

private:
    ContextImplPtr m_impl;
    bool m_cleanup;
};

} // namespace di
