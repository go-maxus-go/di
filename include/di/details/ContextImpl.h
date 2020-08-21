#pragma once

#include <exception>
#include <unordered_map>

#include "Fwd.h"
#include "FactoryTagHolder.h"
#include "SingletonTagHolder.h"


namespace di {

class context;

namespace details {

class ContextImpl
{
public:
    template<class TAG>
    void registerTag(Creator<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createSingletonTagHolder<TAG>(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TAG>
    void registerFactoryTag(Creator<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createFactoryTagHolder<TAG>(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TAG>
    ObjectPtr<TAG> resolve(const context& context) const
    {
        ensureTagIsRegistered<TAG>();
        return retrieveObject<TAG>(context);
    }

    void clear()
    {
        m_tag2holder.clear();
    }

    ContextImpl & operator += (ContextImpl && ctx)
    {
        for (auto it = ctx.m_tag2holder.begin(); it != ctx.m_tag2holder.end(); ++it)
            m_tag2holder[it->first] = std::move(it->second);

        ctx.m_tag2holder.clear();

        return *this;
    }

private:
    template<class TAG>
    void ensureTagIsNotResolved() const
    {
        if (isTagResolved<TAG>())
            throw std::logic_error("di: registering of resolved TAG is not allowed");
    }

    template<class TAG>
    bool isTagResolved() const
    {
        const auto it = m_tag2holder.find(name<TAG>());
        if (it == m_tag2holder.end())
            return false;
        return it->second->isResolved();
    }

    template<class TAG>
    const char * name() const
    {
        return typeid(TAG).name();
    }

    template<class TAG>
    auto createSingletonTagHolder(Creator<TAG> creator) const
    {
        return std::make_unique<SingletonTagHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    auto createFactoryTagHolder(Creator<TAG> creator) const
    {
        return std::make_unique<FactoryTagHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    void putTagHolderInStorage(BaseHolderPtr holder)
    {
        const auto name = this->name<TAG>();
        auto it = m_tag2holder.find(name);
        m_tag2holder.insert(it, std::make_pair(name, std::move(holder)));
    }

    template<class TAG>
    void ensureTagIsRegistered() const
    {
        if (m_tag2holder.find(name<TAG>()) == m_tag2holder.end())
            throw std::logic_error("di: trial to resolve not registered tag");
    }

    template<class TAG>
    auto retrieveObject(const context& context) const
    {
        const auto it = m_tag2holder.find(name<TAG>());
        auto objectAny = it->second->resolve(context);
        return std::any_cast<ObjectPtr<TAG>>(std::move(objectAny));
    }

private:
    using Name = const char *;
    using BaseTagHolderPtr = std::unique_ptr<BaseTagHolder>;
    std::unordered_map<Name, BaseTagHolderPtr> m_tag2holder;
};

} // namespace di
} // namespace details
