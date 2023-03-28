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

            auto d_view = entity_manager.view<DirLight>();
            for (auto [entity, light] : d_view.each())
                material.program->setLight("dir_light", light);

            u32 point_lights_count = 0;
            auto p_view = entity_manager.view<PointLight>();
            for (auto [entity, point_light] : p_view.each())
            {
                material.program->setLight("point_lights[" + std::to_string(point_lights_count) + "]", point_light);
                point_lights_count++;
            }

            u32 spot_lights_count = 0;
            auto s_view = entity_manager.view<SpotLight>();
            for (auto [entity, spot_light] : s_view.each())
            {
                material.program->setLight("spot_lights[" + std::to_string(spot_lights_count) + "]", spot_light);
                spot_lights_count++;
            }

            material.program->setScalar("point_lights_count", point_lights_count);
            material.program->setScalar("spot_lights_count", spot_lights_count);

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