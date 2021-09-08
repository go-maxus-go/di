#pragma once

#include <unordered_map>

#include "Fwd.h"
#include "Error.h"
#include "FactoryHolder.h"
#include "IsBaseOfTemplate.h"
#include "SingletonHolder.h"


namespace di::Details {

class ContextImpl
{
public:
    template<class TAG>
    void put(Creator<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createHolder<TAG>(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TAG>
    auto resolve(const Context& context) const
    {
        ensureTagIsRegistered<TAG>();
        return retrieveObject<TAG>(context);
    }

    ContextImpl& operator += (ContextImpl&& ctx)
    {
        for (auto& name2holder : ctx.m_name2holder)
            m_name2holder[name2holder.first] = std::move(name2holder.second);

        ctx.m_name2holder.clear();

        return *this;
    }

private:
    template<class TAG>
    void ensureTagIsNotResolved() const
    {
        if (isTagResolved<TAG>())
            throw Error("Re-adding of a tag which is already resolved");
    }

    template<class TAG>
    bool isTagResolved() const
    {
        const auto it = m_name2holder.find(typeName<TAG>());
        if (it == m_name2holder.end())
            return false;
        return it->second->isResolved();
    }

    template<class TAG>
    const char* typeName() const
    {
        return typeid(TAG).name();
    }

    template<class TAG>
    auto createHolder(Creator<TAG> creator) const
    {
        if constexpr (isSingletonTag<TAG>())
            return std::make_unique<SingletonHolder<TAG>>(std::move(creator));
        else
            return std::make_unique<FactoryHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    void putTagHolderInStorage(BaseHolderPtr holder)
    {
        const auto tagName = typeName<TAG>();
        auto it = m_name2holder.find(tagName);
        m_name2holder.insert_or_assign(it, tagName, std::move(holder));
    }

    template<class TAG>
    void ensureTagIsRegistered() const
    {
        const auto tagName = typeName<TAG>();
        if (m_name2holder.find(tagName) == m_name2holder.end())
            throw Error("di: trial to resolve not registered tag");
    }

    template<class TAG>
    auto retrieveObject(const Context& context) const
    {
        const auto tagName = typeName<TAG>();
        const auto it = m_name2holder.find(tagName);
        auto objectAny = it->second->resolve(context);
        return castObject<TAG>(std::move(objectAny));
    }

    template<class TAG>
    auto castObject(std::any object) const
    {
        if constexpr (isSingletonTag<TAG>())
            return std::any_cast<Pointer<TAG>>(std::move(object));
        else
            return Pointer<TAG>(std::any_cast<Ref<TAG>*>(object));
    }

    template<class TAG>
    static constexpr bool isSingletonTag()
    {
        constexpr auto isSingleton = IsBaseOfTemplate<SingletonTag, TAG>::value;
        constexpr auto isFactory = IsBaseOfTemplate<FactoryTag, TAG>::value;
        static_assert(isSingleton || isFactory, "Invalid tag type");
        return isSingleton;
    }

private:
    using Name = const char *;
    using BaseHolderPtr = std::unique_ptr<BaseHolder>;
    std::unordered_map<Name, BaseHolderPtr> m_name2holder;
};

} // namespace di::Details
