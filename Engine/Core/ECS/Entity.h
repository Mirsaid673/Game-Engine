#pragma once

#include <entt/entt.hpp>
#include "EntityManager.h"

using EntityID = entt::entity;

class Entity
{
private:
    EntityID entity_id;

public:
    void create()
    {
        entity_id = EntityManager::create();
    }

    template <typename T>
    T &getComponent()
    {
        return EntityManager::get<T>(entity_id);
    }

    template <typename T, class... Args>
    T &addComponent(Args &&...args)
    {
        return EntityManager::emplace<T>(entity_id, args...);
    }
    
};

#include "Entity.inl"