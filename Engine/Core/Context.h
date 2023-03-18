#pragma once

#include "ECS/EntityManager.h"
extern EntityManager entity_manager;

#include "GPU/GPU.h"
#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include "Camera.h"
#include "ECS/SystemManager.h"

extern Window window;
extern Input input;
extern Scene scene;
extern GPU gpu;
extern SystemManager system_manager;