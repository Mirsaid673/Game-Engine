#pragma once

using System = void (*)();
#include <list>

class SystemManager
{
private:
    std::list<System> init_systems;
    std::list<System> update_systems;
    std::list<System> predraw_systems;
    std::list<System> draw_systems;
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

    void addDraw(System s)
    {
        draw_systems.emplace_back(s);
    }

    void addPredraw(System s)
    {
        predraw_systems.emplace_back(s);
    }

//===================
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

    void predraw()
    {
        for (auto system : predraw_systems)
            system();
    }

    void draw()
    {
        for (auto system : draw_systems)
            system();
    }

    void destroy() const
    {
        for (auto system : destroy_systems)
            system();
    }
};