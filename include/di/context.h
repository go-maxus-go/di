#pragma once

#include <cassert>

#include <memory>
#include <functional>
#include <unordered_map>

#include "fwd.h"


namespace di {

class Context
{
    struct BaseHolder
    {
        virtual ~BaseHolder() = default;
    };

    template<class TAG>
    struct Holder : BaseHolder
    {
        using Type = typename TAG::type;
        std::function<std::shared_ptr<Type>()> creator;
        std::shared_ptr<Type> result;
    };

public:
    template<class TAG>
    void registerTag(std::function<std::shared_ptr<typename TAG::type>()> creator)
    {
        auto holder = std::make_unique<Holder<TAG>>();
        holder->creator = std::move(creator);

		auto it = m_tag2holder.find(typeid(TAG).name());
        assert((it == m_tag2holder.end() || dynamic_cast<Holder<TAG>*>(it->second.get())->result)
               && "di: register resolved TAG is not allowed");

        m_tag2holder.insert(it, std::make_pair(typeid(TAG).name(), std::move(holder)));
    }

    template<class TAG>
    std::shared_ptr<typename TAG::type> resolve()
    {
        const auto it = m_tag2holder.find(typeid(TAG).name());
        if (it == m_tag2holder.end())
            return nullptr;

        auto holder = dynamic_cast<Holder<TAG>*>(it->second.get());
        if (holder->result)
            return holder->result;

        holder->result = holder->creator();
		assert(holder->result && "di: impossible to resolve dependency");

        return holder->result;
    }

    void clear()
    {
        m_tag2holder.clear();
    }

private:
    std::unordered_map<const char *, std::unique_ptr<BaseHolder>> m_tag2holder;
};

} // namespace di
