#pragma once

using System = void (*)();
#include <list>

class SystemManager
{
private:
    std::list<System> init_systems;
    std::list<System> update_systems;
    std::list<System> destroy_systems;

public:
    void addInit(System s)
    {
        init_systems.emplace_back(s);
    }

    void addUpdate(System s)
    {
        update_systems.emplace_back(s);
    }

    void init() const
    {
        for (auto system : init_systems)
            system();
    }
    
    void update() const
    {
        for (auto system : update_systems)
            system();
    }

    void destroy() const
    {
        for (auto system : destroy_systems)
            system();
    }
};