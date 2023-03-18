#pragma once

#include <entt/entt.hpp>
#include "EntityManager.h"
#include "Context.h"

using EntityID = entt::entity;

class Entity
{
private:
    EntityID entity_id;

public:
    Entity()
    {
        createEntity();
    }

    ~Entity()
    {
        destroyEntity();
    }
    
    void createEntity()
    {
        entity_id = entity_manager.create();
    }

    void destroyEntity()
    {
        entity_manager.destroy(entity_id);
    }

    template <typename T>
    T &getComponent()
    {
        return entity_manager.get<T>(entity_id);
    }

    template <typename T, class... Args>
    T &addComponent(Args &&...args)
    {
        return entity_manager.emplace<T>(entity_id, args...);
    }

    template <typename T>
    bool hasComponent()
    {
        return entity_manager.try_get<T>(entity_id) != nullptr;
    }

    template <typename T>
    T *tryGet()
    {
        return entity_manager.try_get<T>(entity_id);
    }

    EntityID getEntityID() const { return entity_id; }

    bool operator==(const Entity &other) const { return entity_id == other.entity_id; }
};