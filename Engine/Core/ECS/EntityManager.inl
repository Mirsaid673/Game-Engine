#include "EntityManager.h"

namespace EntityManager
{
    entt::registry registry;

    EntityID create()
    {
        return registry.create();
    }

    template <typename T>
    T &get(EntityID entity)
    {
        registry.get<T>(entity);
    }

    template <typename T, class... Args>
    T &emplace(EntityID entity, Args &&...args)
    {
        return registry.emplace<T>(entity, args...);
    }

    entt::registry &getRegistry()
    {
        return registry;
    }
}