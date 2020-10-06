#pragma once

#include <exception>
#include <unordered_map>

#include "Fwd.h"
#include "../fwd.h"
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
    void registerTag(Creator<TAG> creator)
    {
        ensureTagIsNotResolved<TAG>();
        constexpr auto isSingleton = std::integral_constant<bool, isSingletonTag<TAG>()>();
        auto holder = createHolder<TAG>(std::move(creator), isSingleton);
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

    template<class TAG>
    auto createHolder(Creator<TAG> creator, std::true_type) const
    {
        return std::make_unique<SingletonHolder<TAG>>(std::move(creator));
    }

    template<class TAG>
    auto createHolder(Creator<TAG> creator, std::false_type) const
    {
        return std::make_unique<FactoryHolder<TAG>>(std::move(creator));
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
        constexpr auto isSingleton = isSingletonTag<TAG>();
        return castObject<TAG>(std::move(objectAny), std::integral_constant<bool, isSingleton>());
    }

    template<class TAG>
    auto castObject(std::any object, std::true_type) const
    {
        return std::any_cast<std::shared_ptr<Type<TAG>>>(std::move(object));
    }

    template<class TAG>
    auto castObject(std::any object, std::false_type) const
    {
        return std::unique_ptr<Type<TAG>>(std::any_cast<Type<TAG>*>(object));
    }

    template<class TAG>
    static constexpr bool isSingletonTag()
    {
        constexpr auto isSingleton = is_base_of_template<singleton_tag, TAG>();
        constexpr auto isFactory = is_base_of_template<factory_tag, TAG>();
        static_assert(isSingleton || isFactory, "Tag must be a singleton or a factory tag");
        return isSingleton;
    }

private:
    using Name = const char *;
    using BaseHolderPtr = std::unique_ptr<BaseHolder>;
    std::unordered_map<Name, BaseHolderPtr> m_name2holder;
};

} // namespace di
} // namespace details
