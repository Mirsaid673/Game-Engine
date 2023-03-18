#pragma once

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"

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
        for (auto [entity, render_comp, material, transform] : view.each())
        {
            material.program->use();
            material.program->setMVP(scene.camera->getVP() * transform.getMatrix());
            material.diffuse_texture->use();
            Renderer::drawVertexArray(render_comp.vertex_array);
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