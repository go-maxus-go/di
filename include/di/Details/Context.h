#pragma once

#include <type_traits>

#include "Fwd.h"
#include "Tags.h"
#include "HasDiDeps.h"
#include "ContextImpl.h"
#include "TypeIdentity.h"


namespace di::Details {

/*
 * This class is used for managing dependencies.
 * It holds dependencies and resolves them.
 * It's a good idea to have the only one instance of this class for beginning.
 */
class Context
{
public:
    Context()
        : m_impl(std::make_unique<ContextImpl>())
    {}

    Context(const Context& ctx) = delete;
    Context(Context&& ctx)
    {
        *this = std::move(ctx);
    }

    Context& operator = (const Context&) = delete;
    Context& operator = (Context&& ctx)
    {
        auto newCtxImpl = std::make_unique<ContextImpl>();
        std::swap(m_impl, ctx.m_impl);
        std::swap(ctx.m_impl, newCtxImpl);
        return *this;
    }

    ~Context() = default;

public:
    /*
     * Merge two contexts. The origin Context will get all from the moved one.
     * The moved Context overwrites dependencies if the same tag is used.
     */
    Context& operator += (Context&& ctx)
    {
        *m_impl += std::move(*ctx.m_impl);
        return *this;
    }

    /*
     * Puts a dependency into the context.
     * TYPE - is the concrete type of the TAG's reference or a part of DEPS.
     * DEPS - dependencies provided to the context. They overwrite using di_deps
     * of the concrete class. They are a list of tags.
     *
     * Example of putting a tag with an abstract type reference and two
     * dependencies
     *
     * struct FooTag : di::singleton_tag<IFoo> {};
     * context.put<FooTag, Foo, BarTag, QuxTag>();
     */
    template<class TAG, class TYPE, class ...DEPS>
    void put()
    {
        if constexpr (!std::is_base_of<BaseTag, TYPE>::value)
            put<TAG>(defaultCreator<TAG, TYPE, DEPS...>());
        else
            put<TAG, Type<TAG>, TYPE, DEPS...>();
    }

    /*
     * Register a tag with a concrete type reference. A default constructor will
     * be used. Dependencies should be available in di_deps.
     */
    template<class TAG>
    void put()
    {
        put<TAG, Type<TAG>>();
    }

    /*
     * Put a tag with custom creator function. Creator is a function which
     * accepts a const context and returns a pointer to an object. The type of
     * the object should be the same or static castable to shared_ptr or
     * unique_ptr of tag's reference. For singleton tags the type  should be
     * std::shared_ptr. For factory_tags the type should be std::unique_ptr.
     */
    template<class TAG>
    void put(Creator<TAG> creator)
    {
        m_impl->put<TAG>(std::move(creator));
    }

    /*
     * Resolve necessary dependencies to provide the tag reference object.
     * For a singleton tag the result will be a std::shared_ptr. The same object
     * will be returned everytime.
     * For a factory tag the result will be a std::unique_ptr. A new object will
     * be returned for every call.
     */
    template<class TAG>
    auto resolve() const
    {
        return m_impl->resolve<TAG>(*this);
    }

private:
    template<class TAG, class TYPE, class ...DEPS>
    static constexpr Creator<TAG> defaultCreator()
    {
        if constexpr (sizeof...(DEPS) == 0) {
            if constexpr (HasDiDeps<TYPE>::value)
                return defaultCreator<TAG, TYPE>(Ti<typename TYPE::di_deps>());
            else
                return defaultCreator<TAG, TYPE>(Ti<std::tuple<>>());
        }
        else
            return defaultCreator<TAG, TYPE>(Ti<std::tuple<DEPS...>>());
    }

    template<class TAG, class TYPE, class DEP>
    static constexpr Creator<TAG> defaultCreator(Ti<DEP>)
    {
        return defaultCreator<TAG, TYPE>(Ti<std::tuple<DEP>>());
    }

    template<class TAG, class TYPE, class ...TAGS>
    static constexpr Creator<TAG> defaultCreator(Ti<std::tuple<TAGS...>>)
    {
        return [](const Context& ctx) {
            if constexpr (IsBaseOfTemplate<SingletonTag, TAG>::value)
                return std::make_shared<TYPE>((ctx.resolve<TAGS>())...);
            else
                return std::make_unique<TYPE>((ctx.resolve<TAGS>())...);
        };
    }

private:
    std::unique_ptr<ContextImpl> m_impl;
};

} // namespace di::Details
