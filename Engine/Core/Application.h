#pragma once

#include "Engine.h"

class Application
{
    void init();
    void cleanup();
    void run();

    void update();
};

#include "Application.inl"