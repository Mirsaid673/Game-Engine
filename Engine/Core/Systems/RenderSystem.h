#pragma once

#include "ECS/Entity.h"

#include "Components/Drawable.h"
#include "Components/Material.h"

#include "Context.h"
#include "Mesh.h"
#include "Renderer/Renderer.h"
#include "Scene.h"

namespace RenderSystem
{
    System Update = []()
    {
        auto view = entity_manager.view<Drawable, Material, Transform>();
        for (auto [entity, drawable, material, transform] : view.each())
        {
            material.program->use();

            auto p_view = entity_manager.view<PointLight>();
            u32 i = 0;
            for (auto [entity, point_light] : p_view.each())
            {
                material.program->setLight("point_lights[" + std::to_string(i) + "]", point_light);
                i++;
            }
            material.program->setScalar("point_lights_count", i);

            auto d_view = entity_manager.view<DirLight>();
            for (auto [entity, light] : d_view.each())
                material.program->setLight("dir_light", light);

            material.program->setMVP(scene.camera->getProjection(), scene.camera->getView(), transform.getMatrix());
            material.program->setMaterial("material", material);

            Renderer::drawVertexArray(drawable.vertex_array);
        }
    };

    System Init = []()
    {
        auto view = entity_manager.view<Mesh, Drawable>();

        for (auto [entity, mesh, drawable] : view.each())
        {
            drawable.vertex_array = gpu.loadMesh(mesh);
        }
    };

    void submit()
    {
        system_manager.addInit(Init);
        system_manager.addDraw(Update);
    }
}