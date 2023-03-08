#pragma once

#include "Enums.h"

struct Image
{
    u8* data;
    i32 width;
    i32 height;
    Format format;
    DataType data_type = DataType::UNSIGNED_BYTE;
};
