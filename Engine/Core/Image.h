#pragma once

#include "Enums.h"

struct Image
{
    u8* data;
    u32 width;
    u32 height;
    Format format;
    DataType data_type = DataType::UNSIGNED_BYTE;
};
