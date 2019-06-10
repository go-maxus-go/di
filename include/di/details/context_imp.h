#pragma once

#include <exception>
#include <unordered_map>

#include "fwd.h"
#include "base_tag_holder.h"
#include "singleton_tag_holder.h"
#include "transient_tag_holder.h"


namespace di::details {

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
    void registerTransientTag(Creator<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createTransientTagHolder<TAG>(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TAG>
    ObjectPtr<TAG> resolve() const
    {
        ensureTagIsRegistered<TAG>();
        return retrieveObject<TAG>();
    }

    void clear()
    {
        m_tag2holder.clear();
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
        auto it = m_tag2holder.find(hash<TAG>());
        if (it == m_tag2holder.end())
            return false;
        return it->second->isResolved();
    }

    template<class TAG>
    auto hash() const
    {
        return typeid(TAG).hash_code();
    }

    template<class TAG>
    auto createSingletonTagHolder(Creator<TAG> creator) const
    {
        return std::make_unique<SingletonTagHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    auto createTransientTagHolder(Creator<TAG> creator) const
    {
        return std::make_unique<TransientTagHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    void putTagHolderInStorage(BaseHolderPtr holder)
    {
        const auto hash = this->hash<TAG>();
        auto it = m_tag2holder.find(hash);
        m_tag2holder.insert(it, std::make_pair(hash, std::move(holder)));
    }

    template<class TAG>
    void ensureTagIsRegistered() const
    {
        if (m_tag2holder.find(hash<TAG>()) == m_tag2holder.end())
            throw std::logic_error("di: trial to resolve not registered tag");
    }

    template<class TAG>
    auto retrieveObject() const
    {
        auto it = m_tag2holder.find(hash<TAG>());
        auto objectAny = it->second->resolve();
        return std::any_cast<ObjectPtr<TAG>>(objectAny);
    }

private:
    using Hash = size_t;
    using BaseTagHolderPtr = std::unique_ptr<BaseTagHolder>;
    std::unordered_map<Hash, BaseTagHolderPtr> m_tag2holder;
};

} // namespace di::details
