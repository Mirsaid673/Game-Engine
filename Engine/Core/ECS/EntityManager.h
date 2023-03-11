#pragma once

#include <entt/entt.hpp>

using EntityID = entt::entity;

namespace EntityManager
{
    EntityID create();

    template <typename T>
    T &get(EntityID entity);

    template <typename T, class... Args>
    T &emplace(EntityID entity, Args &&...args);

    entt::registry& getRegistry();
};
