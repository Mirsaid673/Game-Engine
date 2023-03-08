#pragma once

#include <string>
#include "Core.h"

#include "Image.h"
#include "Model.h"

namespace Resource
{
    std::string readFile(const std::string &path);

    Image loadImage(const std::string &path);
    void freeImage(Image& image);

    Model loadModel(const std::string &path);
};