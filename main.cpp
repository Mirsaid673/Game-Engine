#include "Context.h"
#include "Renderer.h"
#include "Shaders/Program.h"
#include "gui.h"
#include "Log.h"
#include "Camera.h"
#include "Resource.h"
#include "Textures/Texture.h"

#include "Node.h"
#include "ECS/ECS.h"
#include "Systems/RenderSystem.h"

struct PosColorVertex
{
    f32 x;
    f32 y;
    f32 z;
    u32 abgr;
    f32 s;
    f32 t;
};

const PosColorVertex vertices[] =
    {
        {-1.0f, 1.0f, 1.0f, 0xff000000, 0.0f, 0.0f},  // 0----1
        {1.0f, 1.0f, 1.0f, 0xff0000ff, 1.0f, 0.0f},   // |  / |
        {-1.0f, -1.0f, 1.0f, 0xff00ff00, 0.0f, 1.0f}, // | /  |
        {1.0f, -1.0f, 1.0f, 0xff00ffff, 1.0f, 1.0f}   // 2----3
};

const u16 indices[] = {0, 1, 2, 1, 3, 2};

void cameraMove(Camera &camera);
void drawIerarchy(Node &root);

int main()
{
    Window::init();

    window.create({800, 600}, "Hello, world");
    window.makeCurrent();

    input.init(window);

    glm::vec3 clear_color(0.8, 0.78, 0.5);
    Renderer::init();
    Renderer::enableDebug();
    Renderer::setViewport(window.getSize());
    Renderer::clearColor(clear_color);
    Renderer::enableDepthTest();

    gui::init(window);

    ProgramHandle basic = gpu.createProgram("../Engine/GPU/Shaders/Shaders/basic.vert", "../Engine/GPU/Shaders/Shaders/basic.frag");

    Model m = Resource::loadModel("model.dae");

    TextureHandle texture = gpu.createTexture(m.meshes[0].texture_path, 4);
    texture->filter(Filter::LINEAR_MIPMAP_LINEAR);

    camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
    camera.transform.origin = {0, 0, -5};

    Node root("root");
    auto &ch = root.addChild("ch");
    ch.addChild("bbb");
    root.addComponent<Mesh>(m.meshes[0]);
    auto &model = root.addComponent<Transform>();
    auto &r_c = root.addComponent<Drawable>();
    auto &m_c = root.addComponent<Material>();
    m_c.diffuse_texture = texture;
    m_c.program = basic;

    model.rotateX(glm::radians(90.0f));

    RenderSystem::submit();

    system_manager.init();
    while (not window.shouldClose())
    {
        input.update();

        if (input.getKeyDown(GLFW_KEY_ESCAPE))
            break;

        cameraMove(camera);

        // renderind
        window.updateSize();
        if (window.resized())
            camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
        Renderer::clearColor(clear_color);
        Renderer::setViewport(window.getSize());
        Renderer::clearBuffers();

        system_manager.update();

        gui::newFrame();

        ImGui::Begin("some window");
        ImGui::ColorPicker3("color", &clear_color.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoBorder);

        drawIerarchy(root);

        ImGui::End();
        gui::endFrame();

        window.swapBuffers();
        Input::updateInput();
    }
    gui::cleanup();
    window.destroy();
    Window::cleanup();
}

void cameraMove(Camera &camera)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    if (not input.getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        input.enableCursor();
        return;
    }
    input.disableCursor();

    float sensetivity = 0.005f;
    float speed = 0.05f;

    glm::vec2 offset = input.getCursorOffset();
    camera.transform.rotate(offset.y * sensetivity, glm::vec3(1, 0, 0));
    camera.transform.rotateY(offset.x * sensetivity);

    glm::vec3 tr(0);
    if (input.getKeyDown(GLFW_KEY_W))
        tr += glm::vec3(0, 0, 1);
    if (input.getKeyDown(GLFW_KEY_S))
        tr += glm::vec3(0, 0, -1);
    if (input.getKeyDown(GLFW_KEY_A))
        tr += glm::vec3(-1, 0, 0);
    if (input.getKeyDown(GLFW_KEY_D))
        tr += glm::vec3(1, 0, 0);

    if (tr != glm::vec3(0))
        camera.transform.translate(glm::normalize(tr) * speed);
}

std::string collapse_title;
void drawIerarchy(Node &root)
{
    if (collapse_title == root.name)
        ImGui::SetNextTreeNodeOpen(false);
    bool open = ImGui::TreeNodeEx(root.name.c_str(),
                                  ImGuiTreeNodeFlags_FramePadding |
                                      ImGuiTreeNodeFlags_DefaultOpen |
                                      (root.getChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0),
                                  "%s", root.name.data());
                                  
    if (ImGui::BeginDragDropTarget())
    {
        auto payload = ImGui::AcceptDragDropPayload("Node");
        if (payload != nullptr)
        {
            Node *n = *(Node **)payload->Data;
            root.addChild(*n);
        }
        ImGui::EndDragDropTarget();
    }

    collapse_title = "";
    if (ImGui::BeginDragDropSource())
    {
        collapse_title = root.name;
        Node *n = &root;
        ImGui::SetDragDropPayload("Node", &n, sizeof(Node **), ImGuiCond_Once);
        ImGui::Text(root.name.c_str());
        ImGui::EndDragDropSource();
    }

    if (open)
    {
        for (auto &child : root.getChildren())
            drawIerarchy(child);
        ImGui::TreePop();
    }
}