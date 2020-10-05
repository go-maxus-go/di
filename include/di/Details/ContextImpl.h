#pragma once

#include <exception>
#include <unordered_map>

#include "Fwd.h"
#include "IsBaseOfTemplate.h"
#include "FactoryHolder.h"
#include "SingletonHolder.h"


namespace di {

class context;

namespace Details {

class ContextImpl
{
public:
    template<class TAG>
    void registerTag(CreatorByTag<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createSingletonHolder(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TYPE>
    void registerType(CreatorByType<TYPE> creator)
    {
        ensureTagIsNotResolved<TYPE>();
        auto holder = createSingletonHolder(std::move(creator));
        putTagHolderInStorage<TYPE>(std::move(holder));
    }

    template<class TAG>
    void registerFactoryTag(CreatorByTag<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        auto holder = createFactoryTagHolder<TAG>(std::move(creator));
        putTagHolderInStorage<TAG>(std::move(holder));
    }

    template<class TAG>
    auto resolve(const context& context) const
    {
        ensureTagIsRegistered<TAG>();
        return retrieveObject<TAG>(context);
    }

    void clear()
    {
        m_name2holder.clear();
    }

    ContextImpl & operator += (ContextImpl && ctx)
    {
        for (auto it = ctx.m_name2holder.begin(); it != ctx.m_name2holder.end(); ++it)
            m_name2holder[it->first] = std::move(it->second);

        ctx.m_name2holder.clear();

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
        const auto it = m_name2holder.find(name<TAG>());
        if (it == m_name2holder.end())
            return false;
        return it->second->isResolved();
    }

    template<class TAG>
    const char * name() const
    {
        return typeid(TAG).name();
    }

    template<class CREATOR>
    auto createSingletonHolder(CREATOR creator) const
    {
        return std::make_unique<SingletonHolder<CREATOR>>(std::move(creator));
    }

    template<class TAG>
    auto createFactoryTagHolder(CreatorByTag<TAG> creator) const
    {
        return std::make_unique<FactoryHolder<CreatorByTag<TAG>>>(std::move(creator));
    }

    template<class TAG>
    void putTagHolderInStorage(BaseHolderPtr holder)
    {
        const auto name = this->name<TAG>();
        auto it = m_name2holder.find(name);
        m_name2holder.insert(it, std::make_pair(name, std::move(holder)));
    }

    template<class TAG>
    void ensureTagIsRegistered() const
    {
        const auto tagName = name<TAG>();
        if (m_name2holder.find(tagName) == m_name2holder.end())
            throw std::logic_error("di: trial to resolve not registered tag");
    }

    template<class TAG>
    auto retrieveObject(const context& context) const
    {
        const auto tagName = name<TAG>();
        const auto it = m_name2holder.find(tagName);
        auto objectAny = it->second->resolve(context);
        return castObject<TAG>(std::move(objectAny), is_base_of_template<Tag, TAG>());
    }

    template<class TAG>
    auto castObject(std::any object, std::true_type) const
    {
        return std::any_cast<ObjectPtr<TAG>>(std::move(object));
    }

    template<class TYPE>
    auto castObject(std::any object, std::false_type) const
    {
        return std::any_cast<Pointer<TYPE>>(std::move(object));
    }

private:
    using Name = const char *;
    using BaseHolderPtr = std::unique_ptr<BaseHolder>;
    std::unordered_map<Name, BaseHolderPtr> m_name2holder;
};

} // namespace di
} // namespace details
